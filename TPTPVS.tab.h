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

#ifndef YY_YY_TPTPVS_TAB_H_INCLUDED
# define YY_YY_TPTPVS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    OPAREN = 258,                  /* OPAREN  */
    CPAREN = 259,                  /* CPAREN  */
    OBRA = 260,                    /* OBRA  */
    CBRA = 261,                    /* CBRA  */
    OKEY = 262,                    /* OKEY  */
    CKEY = 263,                    /* CKEY  */
    COMMA = 264,                   /* COMMA  */
    DOT = 265,                     /* DOT  */
    DDOT = 266,                    /* DDOT  */
    THF = 267,                     /* THF  */
    TFF = 268,                     /* TFF  */
    AXIOM = 269,                   /* AXIOM  */
    HYPOTHESIS = 270,              /* HYPOTHESIS  */
    DEFINITION = 271,              /* DEFINITION  */
    LEMMA = 272,                   /* LEMMA  */
    THEOREM = 273,                 /* THEOREM  */
    CONJECTURE = 274,              /* CONJECTURE  */
    NEGATEDCONJ = 275,             /* NEGATEDCONJ  */
    TYPE = 276,                    /* TYPE  */
    ASSUMPTION = 277,              /* ASSUMPTION  */
    PLAIN = 278,                   /* PLAIN  */
    UNKNOWN = 279,                 /* UNKNOWN  */
    EQUAL_COMB = 280,              /* EQUAL_COMB  */
    DESCRIPTION_COMB = 281,        /* DESCRIPTION_COMB  */
    CHOICE_COMB = 282,             /* CHOICE_COMB  */
    EXISTS_COMB = 283,             /* EXISTS_COMB  */
    FORALL_COMB = 284,             /* FORALL_COMB  */
    DESCRIPTION = 285,             /* DESCRIPTION  */
    CHOICE = 286,                  /* CHOICE  */
    LAMBDA = 287,                  /* LAMBDA  */
    EXISTS = 288,                  /* EXISTS  */
    FORALL = 289,                  /* FORALL  */
    GENTZ_ARROW = 290,             /* GENTZ_ARROW  */
    ARROW = 291,                   /* ARROW  */
    VLINE = 292,                   /* VLINE  */
    AND = 293,                     /* AND  */
    APPLICATION = 294,             /* APPLICATION  */
    UNARY_CONNECTIVE = 295,        /* UNARY_CONNECTIVE  */
    ASSIGNMENT = 296,              /* ASSIGNMENT  */
    IMPLIES = 297,                 /* IMPLIES  */
    IFF = 298,                     /* IFF  */
    INFIX_EQUALITY = 299,          /* INFIX_EQUALITY  */
    INFIX_INEQUALITY = 300,        /* INFIX_INEQUALITY  */
    SUBTYPE_SIGN = 301,            /* SUBTYPE_SIGN  */
    NIFF = 302,                    /* NIFF  */
    NOR = 303,                     /* NOR  */
    NAND = 304,                    /* NAND  */
    TYPED_EXISTS = 305,            /* TYPED_EXISTS  */
    TYPED_FORALL = 306,            /* TYPED_FORALL  */
    LET = 307,                     /* LET  */
    LET1 = 308,                    /* LET1  */
    LET2 = 309,                    /* LET2  */
    DOLLAR_COND = 310,             /* DOLLAR_COND  */
    INCLUDE_HEADER = 311,          /* INCLUDE_HEADER  */
    PLUS = 312,                    /* PLUS  */
    STAR = 313,                    /* STAR  */
    VAR = 314,                     /* VAR  */
    DOLLAR_WORD = 315,             /* DOLLAR_WORD  */
    FUNCTOR = 316,                 /* FUNCTOR  */
    DISTINCT_OBJECT = 317,         /* DISTINCT_OBJECT  */
    NUMBER = 318,                  /* NUMBER  */
    SYSTEM_CONSTANT = 319,         /* SYSTEM_CONSTANT  */
    COMMENT = 320,                 /* COMMENT  */
    INCLUDE_FILE = 321,            /* INCLUDE_FILE  */
    DIV = 322,                     /* DIV  */
    MULTIBLOCK = 323               /* MULTIBLOCK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define OPAREN 258
#define CPAREN 259
#define OBRA 260
#define CBRA 261
#define OKEY 262
#define CKEY 263
#define COMMA 264
#define DOT 265
#define DDOT 266
#define THF 267
#define TFF 268
#define AXIOM 269
#define HYPOTHESIS 270
#define DEFINITION 271
#define LEMMA 272
#define THEOREM 273
#define CONJECTURE 274
#define NEGATEDCONJ 275
#define TYPE 276
#define ASSUMPTION 277
#define PLAIN 278
#define UNKNOWN 279
#define EQUAL_COMB 280
#define DESCRIPTION_COMB 281
#define CHOICE_COMB 282
#define EXISTS_COMB 283
#define FORALL_COMB 284
#define DESCRIPTION 285
#define CHOICE 286
#define LAMBDA 287
#define EXISTS 288
#define FORALL 289
#define GENTZ_ARROW 290
#define ARROW 291
#define VLINE 292
#define AND 293
#define APPLICATION 294
#define UNARY_CONNECTIVE 295
#define ASSIGNMENT 296
#define IMPLIES 297
#define IFF 298
#define INFIX_EQUALITY 299
#define INFIX_INEQUALITY 300
#define SUBTYPE_SIGN 301
#define NIFF 302
#define NOR 303
#define NAND 304
#define TYPED_EXISTS 305
#define TYPED_FORALL 306
#define LET 307
#define LET1 308
#define LET2 309
#define DOLLAR_COND 310
#define INCLUDE_HEADER 311
#define PLUS 312
#define STAR 313
#define VAR 314
#define DOLLAR_WORD 315
#define FUNCTOR 316
#define DISTINCT_OBJECT 317
#define NUMBER 318
#define SYSTEM_CONSTANT 319
#define COMMENT 320
#define INCLUDE_FILE 321
#define DIV 322
#define MULTIBLOCK 323

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 164 "TPTPVS.y"

    int valInt;
    char *valChar; 

#line 208 "TPTPVS.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (yyscan_t scanner, int thread);


#endif /* !YY_YY_TPTPVS_TAB_H_INCLUDED  */
