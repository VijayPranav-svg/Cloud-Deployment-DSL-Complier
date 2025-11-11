%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>
#include <strings.h>

%}

%option caseless

%%

[ \t\r\n]+                 ; 
"{"                        { return LBRACE; }
"}"                        { return RBRACE; }
";"                        { return SEMI; }
":"                        { return COLON; }
"("                        { return LPAREN; }
")"                        { return RPAREN; }
","                        { return COMMA; }
"="                        { return EQUALS; }   

\"[^\"]*\"                 {
                             yylval.str = strdup(yytext + 1);
                             yylval.str[strlen(yylval.str) - 1] = '\0';
                             return STRING;
                          }

[0-9]+                     {
                             yylval.num = atoi(yytext);
                             return NUMBER;
                          }

[a-zA-Z_][a-zA-Z0-9_-]*    {
    if (strcasecmp(yytext,"deployment")==0) return DEPLOYMENT;
    if (strcasecmp(yytext,"provider")==0) return PROVIDER;
    if (strcasecmp(yytext,"region")==0) return REGION;
    if (strcasecmp(yytext,"service")==0) return SERVICE;
    if (strcasecmp(yytext,"image")==0) return IMAGE;
    if (strcasecmp(yytext,"cpu")==0) return CPU;
    if (strcasecmp(yytext,"mem")==0) return MEM;
    if (strcasecmp(yytext,"replicas")==0) return REPLICAS;
    if (strcasecmp(yytext,"optimize")==0) return OPTIMIZE;
    if (strcasecmp(yytext,"cost")==0) return COST;
    if (strcasecmp(yytext,"latency")==0) return LATENCY;
    if (strcasecmp(yytext,"env")==0) return ENV;      
    if (strcasecmp(yytext,"true")==0) return TRUE;
    if (strcasecmp(yytext,"false")==0) return FALSE;

    yylval.str = strdup(yytext);
    return ID;
}


.                          { return yytext[0]; }

%%

int yywrap(void) { return 1; }
