#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

/*
 * codegen.h
 * -----------
 * This header declares functions implemented in codegen.c
 * which handle emitting the final deployment plan or other
 * formatted output based on the AST created by the parser.
 */

/* Emit the deployment plan (JSON-like output) */
void emit_plan(Deployment *d);

/* (Optional) Additional helpers for future extension */
void emit_service(Service *s, int first);

#endif /* CODEGEN_H */
