#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Deployment *create_deployment(const char *name)
{
    Deployment *d = (Deployment *)malloc(sizeof(Deployment));
    d->name = strdup(name);
    d->provider = NULL;
    d->region = NULL;
    d->services = NULL;
    d->constraints = NULL;
    return d;
}

void set_provider(Deployment *d, const char *prov)
{
    if (d->provider)
        free(d->provider);
    d->provider = strdup(prov);
}

void set_region(Deployment *d, const char *reg)
{
    if (d->region)
        free(d->region);
    d->region = strdup(reg);
}

Service *create_service(const char *name)
{
    Service *s = (Service *)malloc(sizeof(Service));
    s->name = strdup(name);
    s->image = NULL;
    s->cpu = 1;
    s->mem = 512;
    s->replicas = 1;
    s->env = NULL; /* initialize env pointer */
    s->next = NULL;
    return s;
}

void add_service(Deployment *d, Service *s)
{
    if (!d->services)
    {
        d->services = s;
    }
    else
    {
        Service *p = d->services;
        while (p->next)
            p = p->next;
        p->next = s;
    }
}

Service *latest_service(Deployment *d)
{
    Service *p = d->services;
    if (!p)
        return NULL;
    while (p->next)
        p = p->next;
    return p;
}

void set_service_image(Service *s, const char *image)
{
    if (!s)
        return;
    if (s->image)
        free(s->image);
    s->image = strdup(image);
}

void set_service_cpu(Service *s, int cpu)
{
    if (!s)
        return;
    s->cpu = cpu;
}

void set_service_mem(Service *s, int mem)
{
    if (!s)
        return;
    s->mem = mem;
}

void set_service_replicas(Service *s, int r)
{
    if (!s)
        return;
    s->replicas = r;
}

Constraint *create_constraint(ConType t, int v)
{
    Constraint *c = (Constraint *)malloc(sizeof(Constraint));
    c->type = t;
    c->value = v;
    c->next = NULL;
    return c;
}

Constraint *append_constraint(Constraint *head, Constraint *c)
{
    if (!head)
        return c;
    Constraint *p = head;
    while (p->next)
        p = p->next;
    p->next = c;
    return head;
}

void set_constraints(Deployment *d, Constraint *c)
{
    d->constraints = c;
}

void free_deployment(Deployment *d)
{
    if (!d)
        return;
    if (d->name)
        free(d->name);
    if (d->provider)
        free(d->provider);
    if (d->region)
        free(d->region);

    Service *s = d->services;
    while (s)
    {
        Service *nx = s->next;
        if (s->name)
            free(s->name);
        if (s->image)
            free(s->image);

        /* free env list, if any */
        EnvVar *ev = s->env;
        while (ev)
        {
            EnvVar *nev = ev->next;
            if (ev->key)
                free(ev->key);
            if (ev->value)
                free(ev->value);
            free(ev);
            ev = nev;
        }

        free(s);
        s = nx;
    }
    Constraint *c = d->constraints;
    while (c)
    {
        Constraint *nc = c->next;
        free(c);
        c = nc;
    }
    free(d);
}

void print_deployment(Deployment *d)
{
    if (!d)
        return;
    printf("Deployment %s\n", d->name);
    if (d->provider)
        printf(" provider: %s\n", d->provider);
    if (d->region)
        printf(" region: %s\n", d->region);
    printf(" Services:\n");
    Service *s = d->services;
    while (s)
    {
        printf("  - %s: image=%s cpu=%d mem=%d replicas=%d\n",
               s->name, s->image ? s->image : "<none>", s->cpu, s->mem, s->replicas);

        /* print env vars if present */
        EnvVar *ev = s->env;
        if (ev)
        {
            printf("    env:\n");
            while (ev)
            {
                printf("      %s = %s\n", ev->key ? ev->key : "(null)", ev->value ? ev->value : "(null)");
                ev = ev->next;
            }
        }
        s = s->next;
    }
    printf(" Constraints:\n");
    Constraint *c = d->constraints;
    while (c)
    {
        printf("  - %s = %d\n", c->type == CON_COST ? "cost" : "latency", c->value);
        c = c->next;
    }
}

EnvVar *create_env(const char *key, const char *value)
{
    EnvVar *e = (EnvVar *)malloc(sizeof(EnvVar));
    e->key = strdup(key);
    e->value = strdup(value);
    e->next = NULL;
    return e;
}

EnvVar *append_env(EnvVar *head, EnvVar *newenv)
{
    if (!head)
        return newenv;
    EnvVar *cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = newenv;
    return head;
}

void add_env(Service *s, EnvVar *env)
{
    if (!s)
        return;
    s->env = append_env(s->env, env);
}