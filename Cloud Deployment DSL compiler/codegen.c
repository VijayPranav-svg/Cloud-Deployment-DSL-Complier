#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include <string.h>

/* Emit a simple JSON-like deployment plan to stdout */

static void emit_service(Service *s, int first)
{
    if (!first)
        printf(",\n");
    printf("    {\n");
    printf("      \"name\": \"%s\",\n", s->name);
    printf("      \"image\": \"%s\",\n", s->image ? s->image : "");
    printf("      \"cpu\": %d,\n", s->cpu);
    printf("      \"mem\": %d,\n", s->mem);
    printf("      \"replicas\": %d,\n", s->replicas);

    /* Emit env array */
    printf("      \"env\": [");
    EnvVar *e = s->env;
    if (!e) {
        printf("],\n"); /* empty array */
    } else {
        printf("\n");
        int first_env = 1;
        while (e)
        {
            if (!first_env)
                printf(",\n");
            /* use proper JSON-like quoting */
            printf("        {\"%s\": \"%s\"}", e->key ? e->key : "", e->value ? e->value : "");
            first_env = 0;
            e = e->next;
        }
        printf("\n      ],\n");
    }
    printf("    }");
}

void emit_plan(Deployment *d)
{
    if (!d)
        return;
    printf("{\n");
    printf("  \"deployment\": \"%s\",\n", d->name);
    if (d->provider)
        printf("  \"provider\": \"%s\",\n", d->provider);
    if (d->region)
        printf("  \"region\": \"%s\",\n", d->region);
    printf("  \"services\": [\n");
    Service *s = d->services;
    int first = 1;
    while (s)
    {
        emit_service(s, first);
        first = 0;
        s = s->next;
    }
    printf("\n  ],\n");

    printf("  \"constraints\": [\n");
    Constraint *c = d->constraints;
    int f = 1;
    while (c)
    {
        if (!f)
            printf(",\n");
        if (c->type == CON_COST)
            printf("    {\"cost\": %d}", c->value);
        else
            printf("    {\"latency\": %d}", c->value);
        f = 0;
        c = c->next;
    }
    printf("\n  ]\n");
    printf("}\n");
}
