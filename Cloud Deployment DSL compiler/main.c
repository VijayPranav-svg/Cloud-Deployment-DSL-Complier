#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yyparse(void);
extern Deployment *root_deployment;
void optimize_deployment(Deployment *d);
void emit_plan(Deployment *d);
extern FILE *yyin;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <input.dsl>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        perror("fopen");
        return 1;
    }
    if (yyparse() != 0)
    {
        fprintf(stderr, "Parsing failed.\n");
        return 2;
    }
    if (!root_deployment)
    {
        fprintf(stderr, "No deployment found in input.\n");
        return 3;
    }

    fprintf(stderr, "=== Parsed Deployment (before optimize) ===\n");
    print_deployment(root_deployment);

    optimize_deployment(root_deployment);

    fprintf(stderr, "=== After Optimization ===\n");
    print_deployment(root_deployment);

    fprintf(stderr, "=== Emitting plan to stdout ===\n");
    emit_plan(root_deployment);

    free_deployment(root_deployment);
    return 0;
}
