#include "optimizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Simple heuristics:
   1) Merge services with same image and similar resources -> single service with summed replicas
   2) If cost constraint present and total CPU high, reduce replicas proportionally
   3) Trim memory if over a naive max per service (demo behavior)
*/

static Service* find_similar(Service *head, Service *s) {
    Service *p = head;
    while (p) {
        if (p!=s && p->image && s->image && strcmp(p->image, s->image)==0
            && p->cpu == s->cpu && p->mem == s->mem) return p;
        p = p->next;
    }
    return NULL;
}

void optimize_deployment(Deployment *d) {
    if (!d) return;

    /* 1) merge identical services (same image, cpu, mem) */
    Service *prev = NULL;
    Service *cur = d->services;
    while (cur) {
        Service *sim = find_similar(d->services, cur);
        if (sim) {
            /* attach replicas to sim and remove cur */
            sim->replicas += cur->replicas;
            Service *to_remove = cur;
            if (prev) prev->next = cur->next;
            else d->services = cur->next;
            cur = cur->next;
            if (to_remove->name) free(to_remove->name);
            if (to_remove->image) free(to_remove->image);
            free(to_remove);
            continue;
        }
        prev = cur;
        cur = cur->next;
    }

    /* compute total cpu*replicas */
    int total_cpu = 0;
    cur = d->services;
    while (cur) {
        total_cpu += cur->cpu * cur->replicas;
        cur = cur->next;
    }

    /* check constraints */
    int cost_limit = -1;
    int latency_limit = -1;
    Constraint *c = d->constraints;
    while (c) {
        if (c->type == CON_COST) cost_limit = c->value;
        if (c->type == CON_LATENCY) latency_limit = c->value;
        c = c->next;
    }

    /* 2) crude cost-based scaling: if cost_limit set, reduce replicas proportionally */
    if (cost_limit > 0 && total_cpu > 0) {
        /* naive cost model: cost unit = total_cpu * 10 */
        int est_cost = total_cpu * 10;
        if (est_cost > cost_limit) {
            double ratio = (double)cost_limit / (double)est_cost;
            if (ratio < 0.1) ratio = 0.1;
            cur = d->services;
            while (cur) {
                int newr = (int)(cur->replicas * ratio);
                if (newr < 1) newr = 1;
                cur->replicas = newr;
                cur = cur->next;
            }
        }
    }

    /* 3) naive memory trim: if service mem > 8192, cap it */
    cur = d->services;
    while (cur) {
        if (cur->mem > 8192) cur->mem = 8192;
        cur = cur->next;
    }

    /* 4) latency heuristic: if latency_limit small (<100) increase replicas of small services */
    if (latency_limit > 0 && latency_limit < 100) {
        cur = d->services;
        while (cur) {
            if (cur->cpu <= 1) cur->replicas += 1; /* quick boost */
            cur = cur->next;
        }
    }

    /* Done */
}
