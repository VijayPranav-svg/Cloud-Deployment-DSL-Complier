#ifndef AST_H
#define AST_H

#include <stddef.h>

/* ---------- Constraint types ---------- */
typedef enum
{
    CON_COST,
    CON_LATENCY
} ConType;

/* ---------- Environment Variable ---------- */
typedef struct EnvVar
{
    char *key;
    char *value;
    struct EnvVar *next;
} EnvVar;

/* ---------- Service ---------- */
typedef struct Service
{
    char *name;
    char *image;
    int cpu;
    int mem;
    int replicas;
    EnvVar *env; /* Linked list of environment variables */
    struct Service *next;
} Service;

/* ---------- Constraint ---------- */
typedef struct Constraint
{
    ConType type;
    int value;
    struct Constraint *next;
} Constraint;

/* ---------- Deployment ---------- */
typedef struct Deployment
{
    char *name;
    char *provider;
    char *region;
    Service *services;
    Constraint *constraints;
} Deployment;

/* ---------- Function Prototypes ---------- */
/* Deployment and service management */
Deployment *create_deployment(const char *name);
void set_provider(Deployment *d, const char *prov);
void set_region(Deployment *d, const char *reg);

Service *create_service(const char *name);
void add_service(Deployment *d, Service *s);
Service *latest_service(Deployment *d);

void set_service_image(Service *s, const char *image);
void set_service_cpu(Service *s, int cpu);
void set_service_mem(Service *s, int mem);
void set_service_replicas(Service *s, int r);

/* Constraints */
Constraint *create_constraint(ConType t, int v);
Constraint *append_constraint(Constraint *head, Constraint *c);
void set_constraints(Deployment *d, Constraint *c);

/* Environment variable helpers */
EnvVar *create_env(const char *key, const char *value);
EnvVar *append_env(EnvVar *head, EnvVar *newenv);
void add_env(Service *s, EnvVar *env);

/* Cleanup and debugging */
void free_deployment(Deployment *d);
void print_deployment(Deployment *d);

#endif
