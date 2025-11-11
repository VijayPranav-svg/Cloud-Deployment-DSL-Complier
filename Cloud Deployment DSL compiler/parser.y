%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"       /* Make sure AST types are known early */
#include "optimizer.h"
#include "codegen.h"

extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;
void yyerror(const char *s);

Deployment *root_deployment;
%}

/* Ensure ast.h is included inside the generated header (y.tab.h) too */
%code requires {
    #include "ast.h"
}

%union {
    char *str;
    int num;
    Service *svc;
    Constraint *con;
    Deployment *dep;
    EnvVar *env;
}

%token <str> ID STRING
%token <num> NUMBER
%token DEPLOYMENT PROVIDER REGION SERVICE IMAGE CPU MEM REPLICAS OPTIMIZE COST LATENCY ENV TRUE FALSE
%token LBRACE RBRACE SEMI COLON LPAREN RPAREN COMMA
%token EQUALS

%type <dep> deployment
%type <svc> service
%type <con> constraint
%type <con> con_list con_list_item
%type <env> env_list env_item


%%

input:
    /* empty */
  | deployment { root_deployment = $1; }
  ;

deployment:
    DEPLOYMENT ID LBRACE {
        /* create deployment early so dep_body actions can use root_deployment */
        root_deployment = create_deployment($2);
        free($2);
    }
    dep_body RBRACE {
        /* return the created deployment */
        $$ = root_deployment;
        root_deployment = NULL; /* avoid accidental reuse */
    }
  ;

dep_body:
    dep_item
  | dep_body dep_item
  ;

dep_item:
    PROVIDER ID SEMI { set_provider(root_deployment, $2); free($2); }
  | REGION ID SEMI { set_region(root_deployment, $2); free($2); }
  | service
  | OPTIMIZE LBRACE con_list RBRACE SEMI { set_constraints(root_deployment, $3); }  /* now consumes trailing SEMI */
  ;

service:
    SERVICE ID LBRACE svc_body RBRACE SEMI {   /* consume trailing semicolon after service block */
        Service *s = create_service($2);
        free($2);
        add_service(root_deployment, s);
    }
  ;

svc_body:
    /* allow empty or multiple items */
    /* empty */ 
  | svc_body svc_item
  ;

svc_item:
    IMAGE STRING SEMI { set_service_image(latest_service(root_deployment), $2); free($2); }
  | CPU NUMBER SEMI { set_service_cpu(latest_service(root_deployment), $2); }
  | MEM NUMBER SEMI { set_service_mem(latest_service(root_deployment), $2); }
  | REPLICAS NUMBER SEMI { set_service_replicas(latest_service(root_deployment), $2); }
  | ENV LBRACE env_list RBRACE SEMI { add_env(latest_service(root_deployment), $3); }
;

env_list:
    env_item                     { $$ = $1; }
  | env_list env_item            { $$ = append_env($1, $2); }
;

env_item:
    ID EQUALS STRING SEMI
    {
        $$ = create_env($1, $3);
    }
;





con_list:
    /* empty */ { $$ = NULL; }
  | con_list_item { $$ = $1; }
  ;

con_list_item:
    constraint { $$ = $1; }
  | con_list_item constraint {
        $$ = append_constraint($1, $2);
    }
  ;

constraint:
    COST NUMBER SEMI { $$ = create_constraint(CON_COST, $2); }
  | LATENCY NUMBER SEMI { $$ = create_constraint(CON_LATENCY, $2); }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
