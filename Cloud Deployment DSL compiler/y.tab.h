/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 18 "parser.y"

    #include "ast.h"

#line 53 "y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    STRING = 259,                  /* STRING  */
    NUMBER = 260,                  /* NUMBER  */
    DEPLOYMENT = 261,              /* DEPLOYMENT  */
    PROVIDER = 262,                /* PROVIDER  */
    REGION = 263,                  /* REGION  */
    SERVICE = 264,                 /* SERVICE  */
    IMAGE = 265,                   /* IMAGE  */
    CPU = 266,                     /* CPU  */
    MEM = 267,                     /* MEM  */
    REPLICAS = 268,                /* REPLICAS  */
    OPTIMIZE = 269,                /* OPTIMIZE  */
    COST = 270,                    /* COST  */
    LATENCY = 271,                 /* LATENCY  */
    ENV = 272,                     /* ENV  */
    TRUE = 273,                    /* TRUE  */
    FALSE = 274,                   /* FALSE  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    SEMI = 277,                    /* SEMI  */
    COLON = 278,                   /* COLON  */
    LPAREN = 279,                  /* LPAREN  */
    RPAREN = 280,                  /* RPAREN  */
    COMMA = 281,                   /* COMMA  */
    EQUALS = 282                   /* EQUALS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define STRING 259
#define NUMBER 260
#define DEPLOYMENT 261
#define PROVIDER 262
#define REGION 263
#define SERVICE 264
#define IMAGE 265
#define CPU 266
#define MEM 267
#define REPLICAS 268
#define OPTIMIZE 269
#define COST 270
#define LATENCY 271
#define ENV 272
#define TRUE 273
#define FALSE 274
#define LBRACE 275
#define RBRACE 276
#define SEMI 277
#define COLON 278
#define LPAREN 279
#define RPAREN 280
#define COMMA 281
#define EQUALS 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "parser.y"

    char *str;
    int num;
    Service *svc;
    Constraint *con;
    Deployment *dep;
    EnvVar *env;

#line 136 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
