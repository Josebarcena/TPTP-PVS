/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "TPTPVS.y"

#include "structs.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


#ifdef _WIN32
    #include <windows.h>
    #define FILE_SEPARATOR '\\'
    #define SO 1
#else
    #define FILE_SEPARATOR '/'
    #define SO 0
#endif

//FUNCTIONS FROM FLEX
typedef union YYSTYPE YYSTYPE;
typedef void *yyscan_t;

extern int yylineno;
extern int yyparse(yyscan_t scanner, int thread);
extern int yylex(yyscan_t scanner, YYSTYPE *yylval);
extern int yylex_init_extra(void* args, yyscan_t *scanner);
extern int yylex_init(yyscan_t *scanner);
void yyset_in(FILE *in_str, yyscan_t scanner);
void yyset_out(FILE *in_str, yyscan_t scanner);
int yyget_lineno(yyscan_t scanner);
void *yyget_extra(yyscan_t scanner);
FILE *yyget_out(yyscan_t scanner);


extern void reset_firstToken(void);
extern void yylex_destroy(yyscan_t scanner);
void yyerror (yyscan_t scanner, int thread, char const *);

//C VARS
int error = 0;
int count = 0;
int maxThread = 0;
int *thread_available;
int numThreads;
time_t rawtime;
struct tm * timeinfo;
pthread_mutex_t availability_mutex;
pthread_mutex_t writeFile_mutex;
pthread_t *threads;

// BISON VARS
Variable** head = NULL;

char **aux;
char **auxComment;
char **fileName;
char **auxVar;
int *existType;
int *existTypePlus;


char *Prepared_types(char *var, int thread){
    if(var != NULL) {
        if(!strcmp(var,"$int")){
            return "int";
        }
        else if(!strcmp(var,"$tType")){
            existType[thread] = 1;
            return "TYPE+";
         
        }
        else if(!strcmp(var,"$i")){
            existTypePlus[thread] = 1;
            return "TYPE+";
        }
        else if(!strcmp(var,"$o")){
            return "bool";
        }
        else if(!strcmp(var,"$rat")){
            return "rat";
        }
        else if(!strcmp(var,"$str")){
            return "string";
        }
        else if(!strcmp(var,"$real")){
            return "real";
        }
        else{
            return var;
        }
    }
    else
        return " ";

}

void ParserArgs(char *str, char *func) {
    char newChar[3];
    if(strcmp(func,"$less") == 0){
        strcpy(newChar,"<");
    }
    else if(strcmp(func,"$lesseq") == 0){
        strcpy(newChar,"<=");
    }
    else if(strcmp(func,"$greater") == 0){
        strcpy(newChar,">");
    }
    else if(strcmp(func,"$greatereq") == 0){
        strcpy(newChar,">=");
    }
    else if(strcmp(func,"$distinct") == 0){
        strcpy(newChar,"=");
    }
    else if(strcmp(func,"$product") == 0){
        strcpy(newChar,"*");
    }
    else if(strcmp(func,"$difference") == 0){
        strcpy(newChar,"-");
    }
    else if(strcmp(func,"$sum") == 0){
        strcpy(newChar,"+");
    }
    char buffer[512] = "";
    int i = 0;

    for (char *pos = str; *pos && i < sizeof(buffer) - 2; ++pos) {
        if (*pos == ',') {
            buffer[i++] = newChar[0];
            if (newChar[1] != '\0') {
                buffer[i++] = newChar[1];
            }
        } else {
            buffer[i++] = *pos;
        }
    }
    buffer[i] = '\0';
    strcpy(str, buffer);
}

int Ends_AnthemDef(const char *str) {
    const char *suffix = "def_ax";
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) {
        return 0;
    }

    return (strcmp(str + str_len - suffix_len, suffix) == 0);
}



#line 230 "TPTPVS.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "TPTPVS.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_OPAREN = 3,                     /* OPAREN  */
  YYSYMBOL_CPAREN = 4,                     /* CPAREN  */
  YYSYMBOL_OBRA = 5,                       /* OBRA  */
  YYSYMBOL_CBRA = 6,                       /* CBRA  */
  YYSYMBOL_OKEY = 7,                       /* OKEY  */
  YYSYMBOL_CKEY = 8,                       /* CKEY  */
  YYSYMBOL_COMMA = 9,                      /* COMMA  */
  YYSYMBOL_DOT = 10,                       /* DOT  */
  YYSYMBOL_DDOT = 11,                      /* DDOT  */
  YYSYMBOL_THF = 12,                       /* THF  */
  YYSYMBOL_TFF = 13,                       /* TFF  */
  YYSYMBOL_AXIOM = 14,                     /* AXIOM  */
  YYSYMBOL_HYPOTHESIS = 15,                /* HYPOTHESIS  */
  YYSYMBOL_DEFINITION = 16,                /* DEFINITION  */
  YYSYMBOL_LEMMA = 17,                     /* LEMMA  */
  YYSYMBOL_THEOREM = 18,                   /* THEOREM  */
  YYSYMBOL_CONJECTURE = 19,                /* CONJECTURE  */
  YYSYMBOL_NEGATEDCONJ = 20,               /* NEGATEDCONJ  */
  YYSYMBOL_TYPE = 21,                      /* TYPE  */
  YYSYMBOL_ASSUMPTION = 22,                /* ASSUMPTION  */
  YYSYMBOL_PLAIN = 23,                     /* PLAIN  */
  YYSYMBOL_UNKNOWN = 24,                   /* UNKNOWN  */
  YYSYMBOL_EQUAL_COMB = 25,                /* EQUAL_COMB  */
  YYSYMBOL_DESCRIPTION_COMB = 26,          /* DESCRIPTION_COMB  */
  YYSYMBOL_CHOICE_COMB = 27,               /* CHOICE_COMB  */
  YYSYMBOL_EXISTS_COMB = 28,               /* EXISTS_COMB  */
  YYSYMBOL_FORALL_COMB = 29,               /* FORALL_COMB  */
  YYSYMBOL_DESCRIPTION = 30,               /* DESCRIPTION  */
  YYSYMBOL_CHOICE = 31,                    /* CHOICE  */
  YYSYMBOL_LAMBDA = 32,                    /* LAMBDA  */
  YYSYMBOL_EXISTS = 33,                    /* EXISTS  */
  YYSYMBOL_FORALL = 34,                    /* FORALL  */
  YYSYMBOL_GENTZ_ARROW = 35,               /* GENTZ_ARROW  */
  YYSYMBOL_ARROW = 36,                     /* ARROW  */
  YYSYMBOL_VLINE = 37,                     /* VLINE  */
  YYSYMBOL_AND = 38,                       /* AND  */
  YYSYMBOL_APPLICATION = 39,               /* APPLICATION  */
  YYSYMBOL_UNARY_CONNECTIVE = 40,          /* UNARY_CONNECTIVE  */
  YYSYMBOL_ASSIGNMENT = 41,                /* ASSIGNMENT  */
  YYSYMBOL_IMPLIES = 42,                   /* IMPLIES  */
  YYSYMBOL_IFF = 43,                       /* IFF  */
  YYSYMBOL_INFIX_EQUALITY = 44,            /* INFIX_EQUALITY  */
  YYSYMBOL_INFIX_INEQUALITY = 45,          /* INFIX_INEQUALITY  */
  YYSYMBOL_SUBTYPE_SIGN = 46,              /* SUBTYPE_SIGN  */
  YYSYMBOL_NIFF = 47,                      /* NIFF  */
  YYSYMBOL_NOR = 48,                       /* NOR  */
  YYSYMBOL_NAND = 49,                      /* NAND  */
  YYSYMBOL_TYPED_EXISTS = 50,              /* TYPED_EXISTS  */
  YYSYMBOL_TYPED_FORALL = 51,              /* TYPED_FORALL  */
  YYSYMBOL_LET = 52,                       /* LET  */
  YYSYMBOL_LET1 = 53,                      /* LET1  */
  YYSYMBOL_LET2 = 54,                      /* LET2  */
  YYSYMBOL_DOLLAR_COND = 55,               /* DOLLAR_COND  */
  YYSYMBOL_INCLUDE_HEADER = 56,            /* INCLUDE_HEADER  */
  YYSYMBOL_PLUS = 57,                      /* PLUS  */
  YYSYMBOL_STAR = 58,                      /* STAR  */
  YYSYMBOL_VAR = 59,                       /* VAR  */
  YYSYMBOL_DOLLAR_WORD = 60,               /* DOLLAR_WORD  */
  YYSYMBOL_FUNCTOR = 61,                   /* FUNCTOR  */
  YYSYMBOL_DISTINCT_OBJECT = 62,           /* DISTINCT_OBJECT  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_SYSTEM_CONSTANT = 64,           /* SYSTEM_CONSTANT  */
  YYSYMBOL_COMMENT = 65,                   /* COMMENT  */
  YYSYMBOL_INCLUDE_FILE = 66,              /* INCLUDE_FILE  */
  YYSYMBOL_DIV = 67,                       /* DIV  */
  YYSYMBOL_MULTIBLOCK = 68,                /* MULTIBLOCK  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_S = 70,                         /* S  */
  YYSYMBOL_tptp_file = 71,                 /* tptp_file  */
  YYSYMBOL_tptp_input = 72,                /* tptp_input  */
  YYSYMBOL_include_file = 73,              /* include_file  */
  YYSYMBOL_comments = 74,                  /* comments  */
  YYSYMBOL_annotated_formula = 75,         /* annotated_formula  */
  YYSYMBOL_thf_annotated = 76,             /* thf_annotated  */
  YYSYMBOL_type = 77,                      /* type  */
  YYSYMBOL_thf_formula = 78,               /* thf_formula  */
  YYSYMBOL_thf_logic_formula = 79,         /* thf_logic_formula  */
  YYSYMBOL_thf_binary_formula = 80,        /* thf_binary_formula  */
  YYSYMBOL_thf_binary_pair = 81,           /* thf_binary_pair  */
  YYSYMBOL_thf_binary_tuple = 82,          /* thf_binary_tuple  */
  YYSYMBOL_thf_or_formula = 83,            /* thf_or_formula  */
  YYSYMBOL_thf_and_formula = 84,           /* thf_and_formula  */
  YYSYMBOL_thf_apply_formula = 85,         /* thf_apply_formula  */
  YYSYMBOL_thf_unitary_formula = 86,       /* thf_unitary_formula  */
  YYSYMBOL_thf_quantified_formula = 87,    /* thf_quantified_formula  */
  YYSYMBOL_thf_quantification = 88,        /* thf_quantification  */
  YYSYMBOL_thf_variable_list = 89,         /* thf_variable_list  */
  YYSYMBOL_thf_variable = 90,              /* thf_variable  */
  YYSYMBOL_thf_typed_variable = 91,        /* thf_typed_variable  */
  YYSYMBOL_thf_unary_formula = 92,         /* thf_unary_formula  */
  YYSYMBOL_thf_atom = 93,                  /* thf_atom  */
  YYSYMBOL_thf_function = 94,              /* thf_function  */
  YYSYMBOL_thf_conn_term = 95,             /* thf_conn_term  */
  YYSYMBOL_thf_conditional = 96,           /* thf_conditional  */
  YYSYMBOL_thf_let = 97,                   /* thf_let  */
  YYSYMBOL_thf_arguments = 98,             /* thf_arguments  */
  YYSYMBOL_thf_type_formula = 99,          /* thf_type_formula  */
  YYSYMBOL_thf_typeable_formula = 100,     /* thf_typeable_formula  */
  YYSYMBOL_thf_subtype = 101,              /* thf_subtype  */
  YYSYMBOL_thf_top_level_type = 102,       /* thf_top_level_type  */
  YYSYMBOL_thf_unitary_type = 103,         /* thf_unitary_type  */
  YYSYMBOL_thf_apply_type = 104,           /* thf_apply_type  */
  YYSYMBOL_thf_binary_type = 105,          /* thf_binary_type  */
  YYSYMBOL_thf_mapping_type = 106,         /* thf_mapping_type  */
  YYSYMBOL_thf_xprod_type = 107,           /* thf_xprod_type  */
  YYSYMBOL_thf_union_type = 108,           /* thf_union_type  */
  YYSYMBOL_thf_sequent = 109,              /* thf_sequent  */
  YYSYMBOL_thf_tuple = 110,                /* thf_tuple  */
  YYSYMBOL_thf_formula_list = 111,         /* thf_formula_list  */
  YYSYMBOL_thf_quantifier = 112,           /* thf_quantifier  */
  YYSYMBOL_fof_quantifier = 113,           /* fof_quantifier  */
  YYSYMBOL_th0_quantifier = 114,           /* th0_quantifier  */
  YYSYMBOL_th1_quantifier = 115,           /* th1_quantifier  */
  YYSYMBOL_thf_pair_connective = 116,      /* thf_pair_connective  */
  YYSYMBOL_thf_unary_connective = 117,     /* thf_unary_connective  */
  YYSYMBOL_th1_unary_connective = 118,     /* th1_unary_connective  */
  YYSYMBOL_atom = 119,                     /* atom  */
  YYSYMBOL_untyped_atom = 120,             /* untyped_atom  */
  YYSYMBOL_constant = 121,                 /* constant  */
  YYSYMBOL_defined_term = 122,             /* defined_term  */
  YYSYMBOL_binary_connective = 123,        /* binary_connective  */
  YYSYMBOL_assoc_connective = 124          /* assoc_connective  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   475

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   201,   201,   218,   221,   224,   226,   230,   246,   249,
     254,   261,   268,   291,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   349,   350,   354,   355,   356,
     357,   366,   367,   368,   371,   385,   386,   387,   390,   393,
     398,   401,   406,   409,   414,   415,   416,   417,   418,   419,
     420,   427,   433,   439,   442,   445,   446,   451,   458,   461,
     467,   468,   469,   470,   475,   476,   479,   516,   517,   518,
     521,   526,   531,   534,   540,   541,   546,   551,   552,   553,
     556,   559,   562,   563,   564,   566,   570,   576,   579,   584,
     587,   592,   595,   600,   601,   604,   605,   610,   611,   616,
     617,   618,   621,   622,   625,   626,   627,   630,   631,   634,
     635,   636,   637,   640,   641,   643,   644,   645,   646,   647,
     651,   652,   663,   666,   669,   670,   673,   674,   675,   676,
     677,   680,   681
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "OPAREN", "CPAREN",
  "OBRA", "CBRA", "OKEY", "CKEY", "COMMA", "DOT", "DDOT", "THF", "TFF",
  "AXIOM", "HYPOTHESIS", "DEFINITION", "LEMMA", "THEOREM", "CONJECTURE",
  "NEGATEDCONJ", "TYPE", "ASSUMPTION", "PLAIN", "UNKNOWN", "EQUAL_COMB",
  "DESCRIPTION_COMB", "CHOICE_COMB", "EXISTS_COMB", "FORALL_COMB",
  "DESCRIPTION", "CHOICE", "LAMBDA", "EXISTS", "FORALL", "GENTZ_ARROW",
  "ARROW", "VLINE", "AND", "APPLICATION", "UNARY_CONNECTIVE", "ASSIGNMENT",
  "IMPLIES", "IFF", "INFIX_EQUALITY", "INFIX_INEQUALITY", "SUBTYPE_SIGN",
  "NIFF", "NOR", "NAND", "TYPED_EXISTS", "TYPED_FORALL", "LET", "LET1",
  "LET2", "DOLLAR_COND", "INCLUDE_HEADER", "PLUS", "STAR", "VAR",
  "DOLLAR_WORD", "FUNCTOR", "DISTINCT_OBJECT", "NUMBER", "SYSTEM_CONSTANT",
  "COMMENT", "INCLUDE_FILE", "DIV", "MULTIBLOCK", "$accept", "S",
  "tptp_file", "tptp_input", "include_file", "comments",
  "annotated_formula", "thf_annotated", "type", "thf_formula",
  "thf_logic_formula", "thf_binary_formula", "thf_binary_pair",
  "thf_binary_tuple", "thf_or_formula", "thf_and_formula",
  "thf_apply_formula", "thf_unitary_formula", "thf_quantified_formula",
  "thf_quantification", "thf_variable_list", "thf_variable",
  "thf_typed_variable", "thf_unary_formula", "thf_atom", "thf_function",
  "thf_conn_term", "thf_conditional", "thf_let", "thf_arguments",
  "thf_type_formula", "thf_typeable_formula", "thf_subtype",
  "thf_top_level_type", "thf_unitary_type", "thf_apply_type",
  "thf_binary_type", "thf_mapping_type", "thf_xprod_type",
  "thf_union_type", "thf_sequent", "thf_tuple", "thf_formula_list",
  "thf_quantifier", "fof_quantifier", "th0_quantifier", "th1_quantifier",
  "thf_pair_connective", "thf_unary_connective", "th1_unary_connective",
  "atom", "untyped_atom", "constant", "defined_term", "binary_connective",
  "assoc_connective", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-81)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,    28,    30,  -122,  -122,    34,  -122,    23,  -122,  -122,
    -122,   -34,   -38,  -122,  -122,    27,    29,  -122,    33,   215,
     215,    31,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,    35,    36,  -122,   271,   271,   271,   159,
     220,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,    37,    39,  -122,    40,    43,  -122,
    -122,    45,  -122,  -122,  -122,  -122,     2,    13,    14,    91,
    -122,   322,  -122,     4,  -122,  -122,  -122,  -122,  -122,    44,
    -122,   -10,  -122,  -122,    -4,    -1,  -122,    32,    59,  -122,
    -122,  -122,  -122,    22,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,    61,    62,    71,   373,  -122,    67,  -122,    77,  -122,
      69,   322,   373,   373,   373,    75,   322,   322,   322,   322,
     322,   322,   322,   373,  -122,  -122,   412,   322,   322,   322,
     322,   322,   322,    25,    42,   373,  -122,    79,    82,  -122,
     373,  -122,  -122,    85,    86,    92,  -122,    94,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,    95,  -122,  -122,    14,
      63,  -122,    68,  -122,  -122,  -122,    68,  -122,  -122,  -122,
    -122,  -122,  -122,    96,    99,    97,  -122,   104,  -122,  -122,
     271,   373,  -122,  -122,  -122,   322,   100,    42,  -122,   106,
     103,  -122,  -122,  -122,  -122,   373,   109,  -122
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     9,    10,     0,     2,     4,     7,     5,
      11,     0,     0,     1,     3,     0,     0,     8,     0,     0,
       0,     0,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     6,     0,     0,     0,     0,
       0,   119,   118,   117,   116,   115,   106,   105,   104,   103,
     102,   131,   132,   113,   112,   127,   126,   109,   110,   128,
     129,   130,   108,   107,     0,     0,    61,   121,   123,   125,
     124,     0,    25,    27,    31,    32,    35,    36,    37,    28,
      44,     0,    45,    46,    60,    63,    47,    48,    29,     0,
      30,     0,    33,    82,    83,    84,    26,    49,     0,    99,
     100,   101,    67,    69,   114,    64,   120,   122,    62,   111,
      68,     0,     0,     0,     0,    93,    97,    49,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,    50,    92,
       0,    94,    96,     0,     0,     0,    72,     0,    12,    39,
      41,    43,    38,    40,    42,    34,     0,    76,    69,    81,
      80,    73,    77,    79,    78,    80,    85,    86,    89,    87,
      88,    90,    91,    56,     0,    54,    55,     0,    13,    98,
       0,     0,    66,    65,    50,     0,     0,     0,    58,     0,
       0,    57,    52,    53,    71,     0,     0,    70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -122,  -122,   110,  -122,  -122,  -122,  -122,  -122,    98,   -32,
     -30,  -122,  -122,  -122,  -122,  -122,  -113,   -69,  -122,  -122,
     -78,  -122,  -122,  -122,   -36,  -122,  -122,  -122,  -122,    -3,
    -122,  -122,  -122,   -75,  -121,  -122,  -122,  -115,  -122,  -122,
      84,   -27,   -26,  -122,  -122,  -122,  -122,    46,   -13,  -122,
    -122,  -122,  -122,  -122,  -122,  -122
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    18,     8,     9,    10,    33,    71,
     116,    73,    74,    75,    76,    77,    78,    79,    80,    81,
     184,   185,   186,    82,   135,    84,    85,    86,    87,   155,
      88,    89,    90,   171,    91,   173,    92,    93,    94,    95,
      96,   117,   156,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      83,    83,    83,    83,    83,   111,    72,    72,   112,    97,
      97,    97,   134,   118,   120,   -74,   172,   176,   178,   179,
     180,   181,   174,   177,   169,   145,   138,    15,    17,    16,
      39,    11,    40,    12,    13,     1,    19,    21,    20,   126,
     121,    35,   122,   123,    36,    37,   124,   139,   140,   125,
     136,   127,   153,   128,   141,   137,   142,   159,   160,   161,
     162,   163,   164,   165,   144,   147,   148,   143,   170,   175,
     175,   175,   175,   175,   172,   149,   150,   152,    83,     2,
     174,   146,   169,   151,   112,   158,    83,    83,    83,   188,
       3,     4,   154,   -75,   190,   191,   192,    83,   193,   194,
     167,   183,   131,   166,   138,   196,   197,   195,   198,    83,
     204,   202,   205,   207,    83,   187,   182,    14,    34,   203,
     201,   157,   113,   168,   189,   132,   170,   -80,   129,   130,
     131,     0,    54,    55,    56,    57,    58,     0,    59,    60,
      61,     0,     0,     0,     0,     0,     0,     0,   -80,   -80,
       0,     0,     0,     0,    83,    83,     0,     0,   199,     0,
      72,   200,   114,    97,    39,   115,    40,     0,     0,    83,
       0,     0,     0,     0,     0,   206,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,     0,     0,    51,    52,     0,    53,
      54,    55,    56,    57,    58,     0,    59,    60,    61,    62,
      63,    64,     0,     0,    65,     0,     0,     0,    66,    67,
      68,    69,    70,   114,     0,    39,     0,    40,   119,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     0,     0,    51,    52,     0,
      53,    54,    55,    56,    57,    58,     0,    59,    60,    61,
      62,    63,    64,     0,    38,    65,    39,     0,    40,    66,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,     0,     0,    51,    52,
       0,    53,    54,    55,    56,    57,    58,     0,    59,    60,
      61,    62,    63,    64,     0,   133,    65,    39,     0,    40,
      66,    67,    68,    69,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     0,     0,    51,
      52,     0,    53,    54,    55,    56,    57,    58,     0,    59,
      60,    61,    62,    63,    64,     0,   114,    65,    39,     0,
      40,    66,    67,    68,    69,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     0,     0,
      51,    52,     0,    53,    54,    55,    56,    57,    58,     0,
      59,    60,    61,    62,    63,    64,     0,     0,    65,     0,
       0,     0,    66,    67,    68,    69,    70,    41,    42,    43,
      44,    45,     0,     0,     0,     0,     0,     0,     0,    51,
      52,     0,    53,    54,    55,    56,    57,    58,     0,    59,
      60,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    66,    67,    68,    69,    70
};

static const yytype_int16 yycheck[] =
{
      36,    37,    38,    39,    40,    37,    36,    37,    38,    36,
      37,    38,    81,    39,    40,    11,   137,   138,   139,   140,
     141,   142,   137,   138,   137,     3,    36,    61,    66,    63,
       5,     3,     7,     3,     0,    12,     9,     4,     9,    37,
       3,    10,     3,     3,     9,     9,     3,    57,    58,     4,
      46,    38,   121,    39,    58,    11,    57,   126,   127,   128,
     129,   130,   131,   132,     5,     4,     4,    35,   137,   138,
     139,   140,   141,   142,   195,     4,     9,     8,   114,    56,
     195,    59,   195,     6,   114,    10,   122,   123,   124,    10,
      67,    68,   122,    11,     9,     9,     4,   133,     4,     4,
     136,    59,    39,   133,    36,     6,     9,    11,     4,   145,
       4,    11,     9,     4,   150,   145,   143,     7,    20,   197,
     195,   124,    38,   136,   150,    79,   195,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    -1,   190,   191,    -1,    -1,   190,    -1,
     190,   191,     3,   190,     5,     6,     7,    -1,    -1,   205,
      -1,    -1,    -1,    -1,    -1,   205,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    -1,    -1,    55,    -1,    -1,    -1,    59,    60,
      61,    62,    63,     3,    -1,     5,    -1,     7,     8,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    37,    38,    -1,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    -1,     3,    55,     5,    -1,     7,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    -1,     3,    55,     5,    -1,     7,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    37,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    -1,     3,    55,     5,    -1,
       7,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    56,    67,    68,    70,    71,    72,    74,    75,
      76,     3,     3,     0,    71,    61,    63,    66,    73,     9,
       9,     4,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    77,    77,    10,     9,     9,     3,     5,
       7,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    37,    38,    40,    41,    42,    43,    44,    45,    47,
      48,    49,    50,    51,    52,    55,    59,    60,    61,    62,
      63,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    92,    93,    94,    95,    96,    97,    99,   100,
     101,   103,   105,   106,   107,   108,   109,   110,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    78,    79,   109,     3,     6,    79,   110,   111,     8,
     111,     3,     3,     3,     3,     4,    37,    38,    39,    37,
      38,    39,   116,     3,    86,    93,    46,    11,    36,    57,
      58,    58,    57,    35,     5,     3,    59,     4,     4,     4,
       9,     6,     8,    86,    79,    98,   111,    98,    10,    86,
      86,    86,    86,    86,    86,    86,    79,    93,   117,    85,
      86,   102,   103,   104,   106,    86,   103,   106,   103,   103,
     103,   103,   110,    59,    89,    90,    91,    79,    10,   111,
       9,     9,     4,     4,     4,    11,     6,     9,     4,    78,
      79,   102,    11,    89,     4,     9,    79,     4
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    71,    71,    72,    72,    72,    73,    74,
      74,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    78,    78,    79,    79,    79,
      79,    80,    80,    80,    81,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    86,    86,    86,    86,
      86,    87,    88,    89,    89,    90,    90,    91,    92,    92,
      93,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      96,    97,    98,    99,   100,   100,   101,   102,   102,   102,
     103,   104,   105,   105,   105,   106,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   110,   110,   111,   111,   112,
     112,   112,   113,   113,   114,   114,   114,   115,   115,   116,
     116,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     119,   119,   120,   121,   122,   122,   123,   123,   123,   123,
     123,   124,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     5,     1,     1,     1,
       1,     1,     9,     9,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       3,     2,     5,     3,     1,     1,     1,     3,     4,     2,
       1,     1,     1,     1,     1,     4,     4,     1,     1,     1,
       8,     6,     1,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     2,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, thread, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner, thread); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t scanner, int thread)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  YY_USE (thread);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t scanner, int thread)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner, thread);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, yyscan_t scanner, int thread)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner, thread);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, thread); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, yyscan_t scanner, int thread)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  YY_USE (thread);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, int thread)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: tptp_file  */
#line 201 "TPTPVS.y"
             {                  FILE *out = yyget_out(scanner);
                                fprintf(out,"%c--Creation-Date: %s", 37, asctime(timeinfo));
                                fprintf(out,"%c--From-File: %s\n", 37, fileName[thread]);
                                if(auxComment[thread] != NULL){
                                    fprintf(out,"%s\n", auxComment[thread]);
                                }
                                fprintf(out,"%s : THEORY \n \tBEGIN", fileName[thread]);
                                fprintf(out,"\n%s", (yyvsp[0].valChar));
                                fprintf(out,"\n\tEND %s",fileName[thread]);
                                free((yyvsp[0].valChar));
                                free(aux[thread]);
                                free(auxComment[thread]);
                                free(fileName[thread]);
                                free(auxVar[thread]);
            }
#line 1857 "TPTPVS.tab.c"
    break;

  case 3: /* tptp_file: tptp_input tptp_file  */
#line 218 "TPTPVS.y"
                                {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5);
                                    snprintf(aux[thread], strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s%s",(yyvsp[-1].valChar), (yyvsp[0].valChar));
                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar)); free((yyvsp[0].valChar));}
#line 1865 "TPTPVS.tab.c"
    break;

  case 4: /* tptp_file: tptp_input  */
#line 221 "TPTPVS.y"
                 {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar));}
#line 1871 "TPTPVS.tab.c"
    break;

  case 5: /* tptp_input: annotated_formula  */
#line 224 "TPTPVS.y"
                              {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar)); //PARSE FORMULAS
                            }
#line 1878 "TPTPVS.tab.c"
    break;

  case 6: /* tptp_input: INCLUDE_HEADER OPAREN include_file CPAREN DOT  */
#line 226 "TPTPVS.y"
                                                    { free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + 20); //PARSE INCLUDEES
                                    snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + 20,"\ninclude %s",(yyvsp[-2].valChar));
                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar));
                                }
#line 1887 "TPTPVS.tab.c"
    break;

  case 7: /* tptp_input: comments  */
#line 230 "TPTPVS.y"
               { //WE PARSE COMMENTS
                    if(auxComment[thread] == NULL){
                        auxComment[thread] = strdup((yyvsp[0].valChar));
                        }
                    else{
                        char *temp;
                        asprintf(&temp, "%s%s", auxComment[thread], (yyvsp[0].valChar));
                        free(auxComment[thread]);
                        auxComment[thread] = strdup(temp);
                        free(temp);
                        }
                 (yyval.valChar) = strdup("");
                 free((yyvsp[0].valChar));
                 }
#line 1906 "TPTPVS.tab.c"
    break;

  case 8: /* include_file: INCLUDE_FILE  */
#line 246 "TPTPVS.y"
                           {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar));}
#line 1912 "TPTPVS.tab.c"
    break;

  case 9: /* comments: DIV  */
#line 249 "TPTPVS.y"
              { free(aux[thread]); aux[thread] = malloc(15 + strlen((yyvsp[0].valChar)));
                                    snprintf(aux[thread],15 + strlen((yyvsp[0].valChar)),"%s\n", (yyvsp[0].valChar));
                                    (yyval.valChar) = strdup(aux[thread]);
                                    free((yyvsp[0].valChar));
                            }
#line 1922 "TPTPVS.tab.c"
    break;

  case 10: /* comments: MULTIBLOCK  */
#line 254 "TPTPVS.y"
                     { free(aux[thread]); aux[thread] = malloc(15 + strlen((yyvsp[0].valChar)));
                                    snprintf(aux[thread],15 + strlen((yyvsp[0].valChar)),"%s\n", (yyvsp[0].valChar));
                                    (yyval.valChar) = strdup(aux[thread]);
                                    free((yyvsp[0].valChar));
                    }
#line 1932 "TPTPVS.tab.c"
    break;

  case 11: /* annotated_formula: thf_annotated  */
#line 261 "TPTPVS.y"
                                 {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar));}
#line 1938 "TPTPVS.tab.c"
    break;

  case 12: /* thf_annotated: THF OPAREN FUNCTOR COMMA type COMMA thf_formula CPAREN DOT  */
#line 268 "TPTPVS.y"
                                                                          {if(strcmp((yyvsp[-4].valChar),"TYPE") == 0){ //we use a TAG for python script
                                                                            free(aux[thread]);
                                                                            aux[thread] = malloc(strlen(auxVar[thread]) + strlen((yyvsp[-2].valChar)) + 25);
                                                                            snprintf(aux[thread],strlen(auxVar[thread]) + strlen((yyvsp[-2].valChar)) + 25,"!DT¡ %s\n", (yyvsp[-2].valChar));
                                                                            (yyval.valChar) = strdup(aux[thread]);  free((yyvsp[-6].valChar)); free((yyvsp[-4].valChar)); free((yyvsp[-2].valChar));
                                                                            }
                                                                            else if(strcmp((yyvsp[-4].valChar),"DEFINITION") == 0){ //we use a TAG for python script
                                                                                free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + 20); 
                                                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + 20,"!DEF¡ %s \n", (yyvsp[-2].valChar));
                                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-6].valChar)); free((yyvsp[-4].valChar)); free((yyvsp[-2].valChar));
                                                                            }
                                                                            /*else if(Ends_AnthemDef($3)){ //we use a TAG for python script
                                                                                free(aux[thread]); aux[thread] = malloc(strlen($7) + 20); 
                                                                                snprintf(aux[thread], strlen($7) + 20,"!DEF¡ %s \n", $7);
                                                                                $$ = strdup(aux[thread]); free($7); free($3); free($5);
                                                                            }*/
                                                                           else{
                                                                                free(aux[thread]); 
                                                                                aux[thread] = malloc(strlen((yyvsp[-6].valChar)) + strlen((yyvsp[-4].valChar)) + strlen((yyvsp[-2].valChar)) + 20); //Direct parse
                                                                                snprintf(aux[thread], strlen((yyvsp[-6].valChar)) + strlen((yyvsp[-4].valChar)) + strlen((yyvsp[-2].valChar)) + 20,"\n\n%s : %s \n \t%s \n", (yyvsp[-6].valChar), (yyvsp[-4].valChar), (yyvsp[-2].valChar));
                                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-6].valChar)); free((yyvsp[-4].valChar)); free((yyvsp[-2].valChar));
                                                                            }
                                                                        }
#line 1966 "TPTPVS.tab.c"
    break;

  case 13: /* thf_annotated: THF OPAREN NUMBER COMMA type COMMA thf_formula CPAREN DOT  */
#line 291 "TPTPVS.y"
                                                               {if(strcmp((yyvsp[-4].valChar),"TYPE") == 0){ //we use a TAG for python script
                                                                            free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-6].valChar)) + strlen((yyvsp[-2].valChar)) + 20);
                                                                            snprintf(aux[thread],strlen((yyvsp[-6].valChar)) + strlen((yyvsp[-2].valChar)) + 20,"!DT¡ %s\n", (yyvsp[-2].valChar));
                                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-4].valChar)); free((yyvsp[-2].valChar)); free((yyvsp[-6].valChar));
                                                                            }
                                                                            else if(strcmp((yyvsp[-4].valChar),"DEFINITION") == 0){ //we use a TAG for python script
                                                                                free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + 20); 
                                                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + 20,"!DEF¡ %s \n", (yyvsp[-2].valChar));
                                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[-6].valChar)); free((yyvsp[-4].valChar));
                                                                            }
                                                                            /*else if(Ends_AnthemDef($3)){ //we use a TAG for python script
                                                                                free(aux[thread]); aux[thread] = malloc(strlen($7) + 20); 
                                                                                snprintf(aux[thread], strlen($7) + 20,"!DEF¡ %s \n", $7);
                                                                                $$ = strdup(aux[thread]); free($7); free($3); free($5);
                                                                            }*/
                                                                           else{
                                                                                free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-6].valChar)) + strlen((yyvsp[-4].valChar)) + strlen((yyvsp[-2].valChar)) + 20); //Direct parse
                                                                                snprintf(aux[thread], strlen((yyvsp[-6].valChar)) + strlen((yyvsp[-4].valChar)) + strlen((yyvsp[-2].valChar)) + 20,"\n\n%s : %s \n\t%s", (yyvsp[-6].valChar), (yyvsp[-4].valChar), (yyvsp[-2].valChar));
                                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-6].valChar)); free((yyvsp[-4].valChar)); free((yyvsp[-2].valChar));
                                                                            }
                                                                        }
#line 1992 "TPTPVS.tab.c"
    break;

  case 14: /* type: AXIOM  */
#line 336 "TPTPVS.y"
            {(yyval.valChar) = strdup("AXIOM"); /* convert bottom of the tree to PVS syntax */}
#line 1998 "TPTPVS.tab.c"
    break;

  case 15: /* type: HYPOTHESIS  */
#line 337 "TPTPVS.y"
                     {(yyval.valChar) = strdup("ASSUME");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
#line 2004 "TPTPVS.tab.c"
    break;

  case 16: /* type: DEFINITION  */
#line 338 "TPTPVS.y"
                     {(yyval.valChar) = strdup("DEFINITION");  /* convert bottom of the tree to PVS syntax */}
#line 2010 "TPTPVS.tab.c"
    break;

  case 17: /* type: LEMMA  */
#line 339 "TPTPVS.y"
                {(yyval.valChar) = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax */}
#line 2016 "TPTPVS.tab.c"
    break;

  case 18: /* type: THEOREM  */
#line 340 "TPTPVS.y"
                  {(yyval.valChar) = strdup("THEOREM");  /* convert bottom of the tree to PVS syntax */}
#line 2022 "TPTPVS.tab.c"
    break;

  case 19: /* type: CONJECTURE  */
#line 341 "TPTPVS.y"
                     {(yyval.valChar) = strdup("CONJECTURE");  /* convert bottom of the tree to PVS syntax */}
#line 2028 "TPTPVS.tab.c"
    break;

  case 20: /* type: NEGATEDCONJ  */
#line 342 "TPTPVS.y"
                      {(yyval.valChar) = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
#line 2034 "TPTPVS.tab.c"
    break;

  case 21: /* type: TYPE  */
#line 343 "TPTPVS.y"
               {(yyval.valChar) = strdup("TYPE");  /* convert bottom of the tree to PVS syntax */}
#line 2040 "TPTPVS.tab.c"
    break;

  case 22: /* type: ASSUMPTION  */
#line 344 "TPTPVS.y"
                     {(yyval.valChar) = strdup("AXIOM");  /* convert bottom of the tree to PVS syntax  --WARNING - NOT DIRECT CONVERSION-- */}
#line 2046 "TPTPVS.tab.c"
    break;

  case 23: /* type: PLAIN  */
#line 345 "TPTPVS.y"
                {(yyval.valChar) = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
#line 2052 "TPTPVS.tab.c"
    break;

  case 24: /* type: UNKNOWN  */
#line 346 "TPTPVS.y"
                  {(yyval.valChar) = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
#line 2058 "TPTPVS.tab.c"
    break;

  case 25: /* thf_formula: thf_logic_formula  */
#line 349 "TPTPVS.y"
                               {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* char comes from thf_logic_formula*/}
#line 2064 "TPTPVS.tab.c"
    break;

  case 26: /* thf_formula: thf_sequent  */
#line 350 "TPTPVS.y"
                      {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* char comes from thf_sequent*/}
#line 2070 "TPTPVS.tab.c"
    break;

  case 27: /* thf_logic_formula: thf_binary_formula  */
#line 354 "TPTPVS.y"
                                      {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* char comes from thf_binary_formula*/}
#line 2076 "TPTPVS.tab.c"
    break;

  case 28: /* thf_logic_formula: thf_unitary_formula  */
#line 355 "TPTPVS.y"
                          { (yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* char comes from thf_unitary_formula*/}
#line 2082 "TPTPVS.tab.c"
    break;

  case 29: /* thf_logic_formula: thf_type_formula  */
#line 356 "TPTPVS.y"
                       {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* char comes from type_formula*/}
#line 2088 "TPTPVS.tab.c"
    break;

  case 30: /* thf_logic_formula: thf_subtype  */
#line 357 "TPTPVS.y"
                  {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* char comes from subtype*/}
#line 2094 "TPTPVS.tab.c"
    break;

  case 31: /* thf_binary_formula: thf_binary_pair  */
#line 366 "TPTPVS.y"
                    {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the pair */}
#line 2100 "TPTPVS.tab.c"
    break;

  case 32: /* thf_binary_formula: thf_binary_tuple  */
#line 367 "TPTPVS.y"
                           {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the tuple */}
#line 2106 "TPTPVS.tab.c"
    break;

  case 33: /* thf_binary_formula: thf_binary_type  */
#line 368 "TPTPVS.y"
                          {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the tuple */}
#line 2112 "TPTPVS.tab.c"
    break;

  case 34: /* thf_binary_pair: thf_unitary_formula thf_pair_connective thf_unitary_formula  */
#line 371 "TPTPVS.y"
                                                                             {  if(strcmp((yyvsp[-1].valChar),"!=") == 0){
                                                                                    free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar))+ strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 15); 
                                                                                    snprintf(aux[thread], strlen((yyvsp[-2].valChar))+ strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 15,"NOT(%s = %s) ", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[-1].valChar)); free((yyvsp[0].valChar));  /*we parser base formula */
                                                                                }   
                                                                                else{
                                                                                    free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar))+ strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                                                    snprintf(aux[thread], strlen((yyvsp[-2].valChar))+ strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s %s %s ", (yyvsp[-2].valChar), (yyvsp[-1].valChar), (yyvsp[0].valChar));
                                                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[-1].valChar)); free((yyvsp[0].valChar));  /*we parser base formula */
                                                                                }
                                                                            }
#line 2128 "TPTPVS.tab.c"
    break;

  case 35: /* thf_binary_tuple: thf_or_formula  */
#line 385 "TPTPVS.y"
                                 {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* sending up the OR formula*/}
#line 2134 "TPTPVS.tab.c"
    break;

  case 36: /* thf_binary_tuple: thf_and_formula  */
#line 386 "TPTPVS.y"
                      {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* sending up the AND formula*/}
#line 2140 "TPTPVS.tab.c"
    break;

  case 37: /* thf_binary_tuple: thf_apply_formula  */
#line 387 "TPTPVS.y"
                        {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* sending up the apply formula*/}
#line 2146 "TPTPVS.tab.c"
    break;

  case 38: /* thf_or_formula: thf_unitary_formula VLINE thf_unitary_formula  */
#line 390 "TPTPVS.y"
                                                              {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15); 
                                                                    snprintf(aux[thread],strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15,"%s OR %s ", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser base formula */}
#line 2154 "TPTPVS.tab.c"
    break;

  case 39: /* thf_or_formula: thf_or_formula VLINE thf_unitary_formula  */
#line 393 "TPTPVS.y"
                                                   {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15); 
                                                    snprintf(aux[thread],strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15,"%s OR %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser base formula */}
#line 2162 "TPTPVS.tab.c"
    break;

  case 40: /* thf_and_formula: thf_unitary_formula AND thf_unitary_formula  */
#line 398 "TPTPVS.y"
                                                             {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15); 
                                                                snprintf(aux[thread],strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15,"%s AND %s ", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser base formula */}
#line 2170 "TPTPVS.tab.c"
    break;

  case 41: /* thf_and_formula: thf_and_formula AND thf_unitary_formula  */
#line 401 "TPTPVS.y"
                                              {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15);  
                                                    snprintf(aux[thread],strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 15,"%s AND %s ", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser compose formula */}
#line 2178 "TPTPVS.tab.c"
    break;

  case 42: /* thf_apply_formula: thf_unitary_formula APPLICATION thf_unitary_formula  */
#line 406 "TPTPVS.y"
                                                                       {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                                            snprintf(aux[thread],strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5," %s(%s) ", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser base formula */}
#line 2186 "TPTPVS.tab.c"
    break;

  case 43: /* thf_apply_formula: thf_apply_formula APPLICATION thf_unitary_formula  */
#line 409 "TPTPVS.y"
                                                        {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5," %s(%s) ", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser compose formula */}
#line 2194 "TPTPVS.tab.c"
    break;

  case 44: /* thf_unitary_formula: thf_quantified_formula  */
#line 414 "TPTPVS.y"
                                            {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the formula */}
#line 2200 "TPTPVS.tab.c"
    break;

  case 45: /* thf_unitary_formula: thf_unary_formula  */
#line 415 "TPTPVS.y"
                        {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the formula */}
#line 2206 "TPTPVS.tab.c"
    break;

  case 46: /* thf_unitary_formula: thf_atom  */
#line 416 "TPTPVS.y"
               {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the formula */}
#line 2212 "TPTPVS.tab.c"
    break;

  case 47: /* thf_unitary_formula: thf_conditional  */
#line 417 "TPTPVS.y"
                      {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the formula */}
#line 2218 "TPTPVS.tab.c"
    break;

  case 48: /* thf_unitary_formula: thf_let  */
#line 418 "TPTPVS.y"
              {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the let */}
#line 2224 "TPTPVS.tab.c"
    break;

  case 49: /* thf_unitary_formula: thf_tuple  */
#line 419 "TPTPVS.y"
                {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the tuple */}
#line 2230 "TPTPVS.tab.c"
    break;

  case 50: /* thf_unitary_formula: OPAREN thf_logic_formula CPAREN  */
#line 420 "TPTPVS.y"
                                      {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + 5);
                                        snprintf(aux[thread],strlen((yyvsp[-1].valChar)) + 5,"(%s)", (yyvsp[-1].valChar));
                                        (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar));/*sending up the tuple */}
#line 2238 "TPTPVS.tab.c"
    break;

  case 51: /* thf_quantified_formula: thf_quantification thf_unitary_formula  */
#line 427 "TPTPVS.y"
                                                               {free(aux[thread]); 
                                                                    aux[thread] = malloc( strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                                    snprintf(aux[thread], strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s %s ", (yyvsp[-1].valChar), (yyvsp[0].valChar));
                                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar)); free((yyvsp[0].valChar));/*we parser quantification formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2247 "TPTPVS.tab.c"
    break;

  case 52: /* thf_quantification: thf_quantifier OBRA thf_variable_list CBRA DDOT  */
#line 433 "TPTPVS.y"
                                                                    {free(aux[thread]);
                                                                        aux[thread] = malloc(strlen((yyvsp[-4].valChar)) + strlen((yyvsp[-2].valChar)) + 10);
                                                                        snprintf(aux[thread], strlen((yyvsp[-4].valChar)) + strlen((yyvsp[-2].valChar)) + 10,"%s (%s) : ", (yyvsp[-4].valChar), (yyvsp[-2].valChar));
                                                                        (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-4].valChar)); free((yyvsp[-2].valChar));/*we parser quantification head --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2256 "TPTPVS.tab.c"
    break;

  case 53: /* thf_variable_list: thf_variable COMMA thf_variable_list  */
#line 439 "TPTPVS.y"
                                                        {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                            snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s , %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser var list --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2264 "TPTPVS.tab.c"
    break;

  case 54: /* thf_variable_list: thf_variable  */
#line 442 "TPTPVS.y"
                   {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the var */}
#line 2270 "TPTPVS.tab.c"
    break;

  case 55: /* thf_variable: thf_typed_variable  */
#line 445 "TPTPVS.y"
                                 {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* convert bottom of the tree to PVS syntax */}
#line 2276 "TPTPVS.tab.c"
    break;

  case 56: /* thf_variable: VAR  */
#line 446 "TPTPVS.y"
          {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[0].valChar))+ 15); 
                                                            snprintf(aux[thread], strlen((yyvsp[0].valChar)) + 15,"%s: int", (yyvsp[0].valChar));
                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[0].valChar));/* convert bottom of the tree to PVS syntax */}
#line 2284 "TPTPVS.tab.c"
    break;

  case 57: /* thf_typed_variable: VAR DDOT thf_top_level_type  */
#line 451 "TPTPVS.y"
                                                {free(auxVar[thread]); free(aux[thread]);
                                                aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5);
                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s: %s", (yyvsp[-2].valChar), Prepared_types((yyvsp[0].valChar), thread));/* Save the var for types name */
                                                auxVar[thread] = strdup((yyvsp[-2].valChar)); (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));
                                                /*sending up the var */}
#line 2294 "TPTPVS.tab.c"
    break;

  case 58: /* thf_unary_formula: thf_unary_connective OPAREN thf_logic_formula CPAREN  */
#line 458 "TPTPVS.y"
                                                                        {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                                            snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"%s(%s)", (yyvsp[-3].valChar), (yyvsp[-1].valChar));
                                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser unary formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2302 "TPTPVS.tab.c"
    break;

  case 59: /* thf_unary_formula: thf_unary_connective VAR  */
#line 461 "TPTPVS.y"
                               {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                                            snprintf(aux[thread], strlen((yyvsp[-1].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s(%s)", (yyvsp[-1].valChar), (yyvsp[0].valChar));
                                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar)); free((yyvsp[0].valChar));/*we parser unary formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2310 "TPTPVS.tab.c"
    break;

  case 60: /* thf_atom: thf_function  */
#line 467 "TPTPVS.y"
                       {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the needed part of the term*/}
#line 2316 "TPTPVS.tab.c"
    break;

  case 61: /* thf_atom: VAR  */
#line 468 "TPTPVS.y"
          {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the var */}
#line 2322 "TPTPVS.tab.c"
    break;

  case 62: /* thf_atom: defined_term  */
#line 469 "TPTPVS.y"
                   { (yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*sending up the needed part of the term*/}
#line 2328 "TPTPVS.tab.c"
    break;

  case 63: /* thf_atom: thf_conn_term  */
#line 470 "TPTPVS.y"
                    {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[0].valChar)) + 5); 
                        snprintf(aux[thread], strlen((yyvsp[0].valChar)) + 5,"(%s)", (yyvsp[0].valChar));
                        (yyval.valChar) = strdup(aux[thread]); free((yyvsp[0].valChar));/*sending up the needed part of the term*/}
#line 2336 "TPTPVS.tab.c"
    break;

  case 64: /* thf_function: atom  */
#line 475 "TPTPVS.y"
                   {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/*we send up the atom*/}
#line 2342 "TPTPVS.tab.c"
    break;

  case 65: /* thf_function: FUNCTOR OPAREN thf_arguments CPAREN  */
#line 476 "TPTPVS.y"
                                          {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"%s (%s)",(yyvsp[-3].valChar), (yyvsp[-1].valChar)); 
                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));}
#line 2350 "TPTPVS.tab.c"
    break;

  case 66: /* thf_function: DOLLAR_WORD OPAREN thf_arguments CPAREN  */
#line 479 "TPTPVS.y"
                                              {if(strcmp((yyvsp[-3].valChar),"$is_int") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"integer?(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp((yyvsp[-3].valChar),"$is_rat") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"rational?(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp((yyvsp[-3].valChar),"$abs") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"abs(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp((yyvsp[-3].valChar),"$floor") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"floor(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp((yyvsp[-3].valChar),"$ceiling") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"ceiling(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp((yyvsp[-3].valChar),"$uminus") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"-%s", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp((yyvsp[-3].valChar),"$distinct") == 0){free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5);
                                                    ParserArgs((yyvsp[-1].valChar), (yyvsp[-3].valChar));
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"NOT(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5); 
                                                    ParserArgs((yyvsp[-1].valChar), (yyvsp[-3].valChar));
                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 5,"(%s)", (yyvsp[-1].valChar)); 
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                }
#line 2390 "TPTPVS.tab.c"
    break;

  case 67: /* thf_conn_term: thf_pair_connective  */
#line 516 "TPTPVS.y"
                                   {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /*we send up the connective*/}
#line 2396 "TPTPVS.tab.c"
    break;

  case 68: /* thf_conn_term: assoc_connective  */
#line 517 "TPTPVS.y"
                       {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /*we send up the connective*/}
#line 2402 "TPTPVS.tab.c"
    break;

  case 69: /* thf_conn_term: thf_unary_connective  */
#line 518 "TPTPVS.y"
                           {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /*we send up the connective*/}
#line 2408 "TPTPVS.tab.c"
    break;

  case 70: /* thf_conditional: DOLLAR_COND OPAREN thf_logic_formula COMMA thf_logic_formula COMMA thf_logic_formula CPAREN  */
#line 521 "TPTPVS.y"
                                                                                                             {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-5].valChar)) + strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 25);
                                                                                                                snprintf(aux[thread], strlen((yyvsp[-5].valChar)) + strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 25,"IF (%s) THEN (%s) else (%s)", (yyvsp[-5].valChar), (yyvsp[-3].valChar), (yyvsp[-1].valChar));
                                                                                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-5].valChar)); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar));/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2416 "TPTPVS.tab.c"
    break;

  case 71: /* thf_let: LET OPAREN thf_unitary_formula COMMA thf_formula CPAREN  */
#line 526 "TPTPVS.y"
                                                                 {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 15);
                                                                    snprintf(aux[thread], strlen((yyvsp[-3].valChar)) + strlen((yyvsp[-1].valChar)) + 15 ,"let(%s) IN %s", (yyvsp[-3].valChar), (yyvsp[-1].valChar));
                                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-3].valChar)); free((yyvsp[-1].valChar)); /*we parser let --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2424 "TPTPVS.tab.c"
    break;

  case 72: /* thf_arguments: thf_formula_list  */
#line 531 "TPTPVS.y"
                                {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* we send up parsed formula_list */}
#line 2430 "TPTPVS.tab.c"
    break;

  case 73: /* thf_type_formula: thf_typeable_formula DDOT thf_top_level_type  */
#line 534 "TPTPVS.y"
                                                               {free(auxVar[thread]); free(aux[thread]);
                                                                aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5);
                                                                snprintf(aux[thread],strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s: %s", (yyvsp[-2].valChar), Prepared_types((yyvsp[0].valChar), thread));
                                                                auxVar[thread] = strdup((yyvsp[-2].valChar)); (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));}
#line 2439 "TPTPVS.tab.c"
    break;

  case 74: /* thf_typeable_formula: thf_atom  */
#line 540 "TPTPVS.y"
                               {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* convert bottom of the tree to PVS syntax */}
#line 2445 "TPTPVS.tab.c"
    break;

  case 75: /* thf_typeable_formula: OPAREN thf_logic_formula CPAREN  */
#line 541 "TPTPVS.y"
                                      {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + 5);
                                            snprintf(aux[thread], strlen((yyvsp[-1].valChar)) + 5,"(%s)", (yyvsp[-1].valChar));
                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar));/*we parser types --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2453 "TPTPVS.tab.c"
    break;

  case 76: /* thf_subtype: thf_atom SUBTYPE_SIGN thf_atom  */
#line 546 "TPTPVS.y"
                                            {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s (SUBTYPE) %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar)); /*we parser the subtype --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2461 "TPTPVS.tab.c"
    break;

  case 77: /* thf_top_level_type: thf_unitary_type  */
#line 551 "TPTPVS.y"
                                     {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* we send up the unitary type */}
#line 2467 "TPTPVS.tab.c"
    break;

  case 78: /* thf_top_level_type: thf_mapping_type  */
#line 552 "TPTPVS.y"
                       {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* we send up the map type */}
#line 2473 "TPTPVS.tab.c"
    break;

  case 79: /* thf_top_level_type: thf_apply_type  */
#line 553 "TPTPVS.y"
                     {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* we send up the apply type */}
#line 2479 "TPTPVS.tab.c"
    break;

  case 80: /* thf_unitary_type: thf_unitary_formula  */
#line 556 "TPTPVS.y"
                                      {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar));/*store var name in $$*/ }
#line 2485 "TPTPVS.tab.c"
    break;

  case 81: /* thf_apply_type: thf_apply_formula  */
#line 559 "TPTPVS.y"
                                  {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar));/* we send up the apply formula */}
#line 2491 "TPTPVS.tab.c"
    break;

  case 82: /* thf_binary_type: thf_mapping_type  */
#line 562 "TPTPVS.y"
                                  { (yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* store in binary_type */ }
#line 2497 "TPTPVS.tab.c"
    break;

  case 83: /* thf_binary_type: thf_xprod_type  */
#line 563 "TPTPVS.y"
                      { (yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* store in binary_type */ }
#line 2503 "TPTPVS.tab.c"
    break;

  case 84: /* thf_binary_type: thf_union_type  */
#line 564 "TPTPVS.y"
                      { (yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* store in binary_type */ }
#line 2509 "TPTPVS.tab.c"
    break;

  case 85: /* thf_mapping_type: thf_unitary_type ARROW thf_unitary_type  */
#line 566 "TPTPVS.y"
                                                          {free(aux[thread]); 
                                                            aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                            snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s -> %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser the arrow basic formula*/}
#line 2518 "TPTPVS.tab.c"
    break;

  case 86: /* thf_mapping_type: thf_unitary_type ARROW thf_mapping_type  */
#line 570 "TPTPVS.y"
                                              {free(aux[thread]); 
                                                aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5);
                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s -> %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser the arrow compose formula*/}
#line 2527 "TPTPVS.tab.c"
    break;

  case 87: /* thf_xprod_type: thf_unitary_type STAR thf_unitary_type  */
#line 576 "TPTPVS.y"
                                                       {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5);
                                                            snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s * %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser the star basic formula*/}
#line 2535 "TPTPVS.tab.c"
    break;

  case 88: /* thf_xprod_type: thf_xprod_type STAR thf_unitary_type  */
#line 579 "TPTPVS.y"
                                           {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s * %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser the star compose formula*/}
#line 2543 "TPTPVS.tab.c"
    break;

  case 89: /* thf_union_type: thf_unitary_type PLUS thf_unitary_type  */
#line 584 "TPTPVS.y"
                                                       { free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5);
                                                            snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s + %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                            (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser the plus compose formula*/}
#line 2551 "TPTPVS.tab.c"
    break;

  case 90: /* thf_union_type: thf_union_type PLUS thf_unitary_type  */
#line 587 "TPTPVS.y"
                                           {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s + %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar)); /*we parser the plus compose formula*/}
#line 2559 "TPTPVS.tab.c"
    break;

  case 91: /* thf_sequent: thf_tuple GENTZ_ARROW thf_tuple  */
#line 592 "TPTPVS.y"
                                             {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 20); 
                                                snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 20,"%s IMPLIES(GENTZ) %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar)); /*we parser the sequent implies*/}
#line 2567 "TPTPVS.tab.c"
    break;

  case 92: /* thf_sequent: OPAREN thf_sequent CPAREN  */
#line 595 "TPTPVS.y"
                                {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + 5); 
                                        snprintf(aux[thread],strlen((yyvsp[-1].valChar)) + 5,"(%s)", (yyvsp[-1].valChar));
                                        (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar)); /*we parser the parenthesis sequent */}
#line 2575 "TPTPVS.tab.c"
    break;

  case 93: /* thf_tuple: OBRA CBRA  */
#line 600 "TPTPVS.y"
                     { (yyval.valChar) = strdup("[]"); /*we parser the empty bracket formula */}
#line 2581 "TPTPVS.tab.c"
    break;

  case 94: /* thf_tuple: OBRA thf_formula_list CBRA  */
#line 601 "TPTPVS.y"
                                 {free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + 5);
                                        snprintf(aux[thread],strlen((yyvsp[-1].valChar)) + 5,"[%s]", (yyvsp[-1].valChar));
                                        (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar)); /*we parser the bracket formula */}
#line 2589 "TPTPVS.tab.c"
    break;

  case 95: /* thf_tuple: OKEY CKEY  */
#line 604 "TPTPVS.y"
                { (yyval.valChar) = strdup("{}"); /*we parser the empty braces formula */}
#line 2595 "TPTPVS.tab.c"
    break;

  case 96: /* thf_tuple: OKEY thf_formula_list CKEY  */
#line 605 "TPTPVS.y"
                                 { free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-1].valChar)) + 5); 
                                        snprintf(aux[thread],strlen((yyvsp[-1].valChar)) + 5,"{%s}", (yyvsp[-1].valChar));
                                        (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-1].valChar));/*we parser the braces formula */}
#line 2603 "TPTPVS.tab.c"
    break;

  case 97: /* thf_formula_list: thf_logic_formula  */
#line 610 "TPTPVS.y"
                                    {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar));/* in this case we send directly the formula */}
#line 2609 "TPTPVS.tab.c"
    break;

  case 98: /* thf_formula_list: thf_logic_formula COMMA thf_formula_list  */
#line 611 "TPTPVS.y"
                                               { free(aux[thread]); aux[thread] = malloc(strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5); 
                                                    snprintf(aux[thread], strlen((yyvsp[-2].valChar)) + strlen((yyvsp[0].valChar)) + 5,"%s , %s", (yyvsp[-2].valChar), (yyvsp[0].valChar));
                                                    (yyval.valChar) = strdup(aux[thread]); free((yyvsp[-2].valChar)); free((yyvsp[0].valChar));/*we parser the , formula */}
#line 2617 "TPTPVS.tab.c"
    break;

  case 99: /* thf_quantifier: fof_quantifier  */
#line 616 "TPTPVS.y"
                               {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* we send up the saved token */}
#line 2623 "TPTPVS.tab.c"
    break;

  case 100: /* thf_quantifier: th0_quantifier  */
#line 617 "TPTPVS.y"
                     {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* we send up the saved token */}
#line 2629 "TPTPVS.tab.c"
    break;

  case 101: /* thf_quantifier: th1_quantifier  */
#line 618 "TPTPVS.y"
                     {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* we send up the saved token */}
#line 2635 "TPTPVS.tab.c"
    break;

  case 102: /* fof_quantifier: FORALL  */
#line 621 "TPTPVS.y"
                       {(yyval.valChar) = strdup("FORALL "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
#line 2641 "TPTPVS.tab.c"
    break;

  case 103: /* fof_quantifier: EXISTS  */
#line 622 "TPTPVS.y"
             {(yyval.valChar) = strdup("EXISTS "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
#line 2647 "TPTPVS.tab.c"
    break;

  case 104: /* th0_quantifier: LAMBDA  */
#line 625 "TPTPVS.y"
                       {(yyval.valChar) = strdup(" LAMBDA "); /* convert bottom of the tree to PVS syntax */}
#line 2653 "TPTPVS.tab.c"
    break;

  case 105: /* th0_quantifier: CHOICE  */
#line 626 "TPTPVS.y"
             {(yyval.valChar) = strdup("APPLY"); /* convert bottom of the tree to PVS syntax */}
#line 2659 "TPTPVS.tab.c"
    break;

  case 106: /* th0_quantifier: DESCRIPTION  */
#line 627 "TPTPVS.y"
                  {(yyval.valChar) = strdup("APPLY"); /* --WARNING - NOT DIRECT CONVERSION-- */}
#line 2665 "TPTPVS.tab.c"
    break;

  case 107: /* th1_quantifier: TYPED_FORALL  */
#line 630 "TPTPVS.y"
                             {(yyval.valChar) = strdup("FORALL "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
#line 2671 "TPTPVS.tab.c"
    break;

  case 108: /* th1_quantifier: TYPED_EXISTS  */
#line 631 "TPTPVS.y"
                     {(yyval.valChar) = strdup("EXISTS "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
#line 2677 "TPTPVS.tab.c"
    break;

  case 109: /* thf_pair_connective: INFIX_EQUALITY  */
#line 634 "TPTPVS.y"
                                    {(yyval.valChar) = strdup(" = "); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2683 "TPTPVS.tab.c"
    break;

  case 110: /* thf_pair_connective: INFIX_INEQUALITY  */
#line 635 "TPTPVS.y"
                       {(yyval.valChar) = strdup("!="); /* --WARNING - NOT DIRECT CONVERSION--*/}
#line 2689 "TPTPVS.tab.c"
    break;

  case 111: /* thf_pair_connective: binary_connective  */
#line 636 "TPTPVS.y"
                        {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* we send up binary_connective Char */}
#line 2695 "TPTPVS.tab.c"
    break;

  case 112: /* thf_pair_connective: ASSIGNMENT  */
#line 637 "TPTPVS.y"
                 { (yyval.valChar) = strdup(":"); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
#line 2701 "TPTPVS.tab.c"
    break;

  case 113: /* thf_unary_connective: UNARY_CONNECTIVE  */
#line 640 "TPTPVS.y"
                                       {{(yyval.valChar) = strdup("NOT"); /* convert bottom of the tree to PVS syntax */}}
#line 2707 "TPTPVS.tab.c"
    break;

  case 114: /* thf_unary_connective: th1_unary_connective  */
#line 641 "TPTPVS.y"
                           {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /**/}
#line 2713 "TPTPVS.tab.c"
    break;

  case 115: /* th1_unary_connective: FORALL_COMB  */
#line 643 "TPTPVS.y"
                                  { (yyval.valChar) = strdup("FORALL"); /* bottom of the tree we save here the token*/}
#line 2719 "TPTPVS.tab.c"
    break;

  case 116: /* th1_unary_connective: EXISTS_COMB  */
#line 644 "TPTPVS.y"
                  { (yyval.valChar) = strdup("EXISTS");/* bottom of the tree we save here the token*/}
#line 2725 "TPTPVS.tab.c"
    break;

  case 117: /* th1_unary_connective: CHOICE_COMB  */
#line 645 "TPTPVS.y"
                 { (yyval.valChar) = strdup("choice");/* bottom of the tree we save here the token*/}
#line 2731 "TPTPVS.tab.c"
    break;

  case 118: /* th1_unary_connective: DESCRIPTION_COMB  */
#line 646 "TPTPVS.y"
                       { (yyval.valChar) = strdup("THE");/* bottom of the tree we save here the token*/}
#line 2737 "TPTPVS.tab.c"
    break;

  case 119: /* th1_unary_connective: EQUAL_COMB  */
#line 647 "TPTPVS.y"
                 {(yyval.valChar) = strdup("=");/* bottom of the tree we save here the token*/ }
#line 2743 "TPTPVS.tab.c"
    break;

  case 120: /* atom: untyped_atom  */
#line 651 "TPTPVS.y"
                   {(yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar)); /*send up the functor*/}
#line 2749 "TPTPVS.tab.c"
    break;

  case 121: /* atom: DOLLAR_WORD  */
#line 652 "TPTPVS.y"
                  {
        if (strcmp((yyvsp[0].valChar), "$true") == 0) {
            (yyval.valChar) = strdup("TRUE");
        } else if (strcmp((yyvsp[0].valChar), "$false") == 0) {
            (yyval.valChar) = strdup("FALSE");
        } else {
            (yyval.valChar) = strdup(Prepared_types((yyvsp[0].valChar), thread));
        }
        free((yyvsp[0].valChar)); /* bottom of the tree we save here the token */}
#line 2763 "TPTPVS.tab.c"
    break;

  case 122: /* untyped_atom: constant  */
#line 663 "TPTPVS.y"
                       {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /* we send up the FUNCTOR */}
#line 2769 "TPTPVS.tab.c"
    break;

  case 123: /* constant: FUNCTOR  */
#line 666 "TPTPVS.y"
                  {(yyval.valChar) = strdup((yyvsp[0].valChar)); free((yyvsp[0].valChar)); /*bottom of the tree we save here the token*/}
#line 2775 "TPTPVS.tab.c"
    break;

  case 124: /* defined_term: NUMBER  */
#line 669 "TPTPVS.y"
                     { (yyval.valChar) = strdup((yyvsp[0].valChar));  free((yyvsp[0].valChar)); /*bottom of the tree we save here the token*/}
#line 2781 "TPTPVS.tab.c"
    break;

  case 125: /* defined_term: DISTINCT_OBJECT  */
#line 670 "TPTPVS.y"
                      {(yyval.valChar) = strdup((yyvsp[0].valChar));   free((yyvsp[0].valChar));/*bottom of the tree we save here the token*/}
#line 2787 "TPTPVS.tab.c"
    break;

  case 126: /* binary_connective: IFF  */
#line 673 "TPTPVS.y"
                       {(yyval.valChar) = strdup(" IFF "); /*we convert the token to PVS*/}
#line 2793 "TPTPVS.tab.c"
    break;

  case 127: /* binary_connective: IMPLIES  */
#line 674 "TPTPVS.y"
              {(yyval.valChar) = strdup(" IMPLIES "); /* --WARNING - NOT DIRECT CONVERSION-- */}
#line 2799 "TPTPVS.tab.c"
    break;

  case 128: /* binary_connective: NIFF  */
#line 675 "TPTPVS.y"
           {(yyval.valChar) = strdup("NIFF"); /* --WARNING - NOT DIRECT CONVERSION-- */}
#line 2805 "TPTPVS.tab.c"
    break;

  case 129: /* binary_connective: NOR  */
#line 676 "TPTPVS.y"
          {(yyval.valChar) = strdup("NOR"); /* --WARNING - NOT DIRECT CONVERSION-- */}
#line 2811 "TPTPVS.tab.c"
    break;

  case 130: /* binary_connective: NAND  */
#line 677 "TPTPVS.y"
           {(yyval.valChar) = strdup("NAND"); /* --WARNING - NOT DIRECT CONVERSION-- */}
#line 2817 "TPTPVS.tab.c"
    break;

  case 131: /* assoc_connective: VLINE  */
#line 680 "TPTPVS.y"
                        {(yyval.valChar) = strdup("OR"); /*bottom of the tree we save here the token*/}
#line 2823 "TPTPVS.tab.c"
    break;

  case 132: /* assoc_connective: AND  */
#line 681 "TPTPVS.y"
          {(yyval.valChar) = strdup("AND"); /*bottom of the tree we save here the token*/}
#line 2829 "TPTPVS.tab.c"
    break;


#line 2833 "TPTPVS.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (scanner, thread, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner, thread);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner, thread);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, thread, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner, thread);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner, thread);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 684 "TPTPVS.y"


void InitializeVars(int numThreads){
    fileName = malloc(numThreads * sizeof(char *));
    aux = malloc(numThreads * sizeof(char *));
    auxVar = malloc(numThreads * sizeof(char *));
    head = malloc(numThreads * sizeof(Variable));
    auxComment = malloc(numThreads * sizeof(char *));
    existType = malloc(numThreads * sizeof(int *));
    existTypePlus = malloc(numThreads * sizeof(int *));
}

void FreeVars(){
    free(fileName);
    free(aux);
    free(head);
    free(auxComment);
    free(thread_available);
    free(auxVar);
    free(existType);
    free(existTypePlus);
}


void FreeThread(int numThread){
    pthread_mutex_lock(&availability_mutex);
        if(thread_available[numThread] == 0){
            thread_available[numThread] = 1;
            pthread_mutex_unlock(&availability_mutex);
            return;
        }
        else{
            perror("ERROR: 487 ");
            pthread_mutex_unlock(&availability_mutex);
            return;
        }
    }
    
int FindAvailableThread(int numThreads){
    pthread_mutex_lock(&availability_mutex);
    for(int i = 0; i < numThreads; i++){
        if(thread_available[i] == 1){
            thread_available[i] = 0;
            pthread_mutex_unlock(&availability_mutex);
            return i;
        }
    }
    pthread_mutex_unlock(&availability_mutex);
    return -1;
}


//Function to parse each file
void *ProcessFile(void *arg){
    FILE *outputFile;
    char *outputFileName;
    char command[2048];
    ThreadArgs *data = (ThreadArgs *)arg;
    ScanVars *scanVars = malloc(sizeof(ScanVars));
    size_t len = 0;
    

    //printf("Processing FILE : %s \n",data->file);
   FILE *in = fopen(data->file, "r");
        if (in == NULL) {
            printf("ERROR: File cant be opened.\r\n");
            return NULL;
        }
        else {
           

            char *baseName = strrchr(data->file, FILE_SEPARATOR);
            len = strlen(baseName);
            if (len >= 2 && strcmp(baseName + len - 2, ".p") != 0) {
                printf("ERROR: File %s is not a TPTP file.\n", data->file);
                fclose(in);
                return NULL;
            }
            if (baseName) {
                baseName++;
            } else {
                baseName = data->file;
            }
            outputFileName = malloc(strlen(baseName) + 15);
            snprintf(outputFileName,strlen(baseName) + 15, "Output%c%s.pvs", FILE_SEPARATOR, baseName);
            fileName[data->numThread] = strdup(baseName);
            printf("Creating FILE : %.*spvs \n", (int)(strlen(outputFileName) - 5), outputFileName);
            outputFile = fopen(outputFileName, "w");

            if (outputFile == NULL) {
                perror("ERROR: OutputFile cant be created.\n");
                fclose(in);
                return NULL;
            }
            head[data->numThread] = NULL;
            auxComment[data->numThread] = NULL;
            aux[data->numThread] = NULL;
            auxVar[data->numThread] = NULL;
            existType[data->numThread] = 0;
            existTypePlus[data->numThread] = 0;

            scanVars->firstToken = 1;
            scanVars->fileName = strdup(fileName[data->numThread]);

            yyscan_t scanner;
            yylex_init_extra(scanVars, &scanner);
            yyset_out(outputFile, scanner);
            yyset_in(in, scanner);
            yyparse(scanner, data->numThread);

            fclose(outputFile);
            fclose(in);
            yylex_destroy(scanner);
        }
    

    snprintf(command, sizeof(command), "python3 parser.py %s", outputFileName);
    system(command);

    free(outputFileName);
    FreeThread(data->numThread);
    free(data);
    free(scanVars->fileName);
    free(scanVars);
    pthread_exit(NULL);
} 

void ReadDir(char *dir){
    DIR *dr = opendir(dir);
    struct dirent *de;
    char fullPath[1024 + strlen(dir)];

    int currentThread = FindAvailableThread(numThreads);
    
    maxThread = currentThread;
    

    if (dr == NULL){ 
        perror("Could not open current directory" ); 
        return;
    }

    while ((de = readdir(dr)) != NULL){ // we send each file != . | ..
        if(de->d_type == DT_REG){
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, de->d_name);
            ThreadArgs *args = malloc(sizeof(ThreadArgs));
            args->numThread = currentThread;
            strcpy(args->file,fullPath);
            
            if(pthread_create(&threads[currentThread], NULL, ProcessFile, (void *)args)){
                char auxPerror[8000];
                snprintf(auxPerror,sizeof(auxPerror),"ERROR: cannot create THREAD %d processing FILE %s", currentThread, fullPath);
                perror(auxPerror);
                exit(EXIT_FAILURE);
            }
            while((currentThread = FindAvailableThread(numThreads)) == -1){
                usleep(100);
            }
            maxThread = currentThread > maxThread ? currentThread : maxThread;
        }
        else if(de->d_type == DT_DIR){
            if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, de->d_name);
                ReadDir(fullPath);
            }
        }
    }
    closedir(dr);

}

int main(int argc, char *argv[]) {
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    struct stat st = {0};

    struct timeval start_time, end_time;
    
    gettimeofday(&start_time, NULL);
    numThreads = 1;
    if(SO == 0){ //How we know the thread changes for each SO
       if(argc > 3){
            if(strcmp(argv[3],"-h") == 0){
                if(atoi(argv[4]) > 1)
                    numThreads = atoi(argv[4]);    
            }
       }
    }
    else{
        if(argc > 3){
            if(strcmp(argv[3],"-h") == 0){
                if(atoi(argv[4]) > 1)
                    numThreads = atoi(argv[4]);    
            }
        }    
    }
    thread_available = malloc(numThreads * sizeof(int));
    for(int i = 0; i < numThreads; i++){
        thread_available[i] = 1;
    }


    threads = malloc(numThreads * sizeof(pthread_t));
    pthread_mutex_init(&availability_mutex, NULL);

        switch (argc) {
            case 1:	
                FILE *in = stdin;
                InitializeVars(1);
                fileName[0] = strdup("TPTPS.pvs");

                yyscan_t scanner;
                yylex_init(&scanner);
                yyset_in(in, scanner);
                yyparse(scanner, 0);
                yylex_destroy(scanner);
                fclose(in);
                FreeVars();
                break;
            case 2: 
                printf("ERROR INVALID NUMBER OF ARGUMENTS, EXAMPLE: \n \b -f file.p, -d directory");
                break;
            case 3:
            case 4:
            case 5:
                if (stat("Output", &st) == -1) {
                        printf("Creating Output Directory...\n");
                        if (mkdir("Output", 0700) == -1) {
                            perror("ERROR: Cant create 'Output'");
                            return 0;
                        }
                    }
                if(strcmp(argv[1],"-f") == 0){
                    InitializeVars(1);
                    ThreadArgs *args = malloc(sizeof(ThreadArgs));
                    args->numThread = FindAvailableThread(1);
                    printf("Processing thread: %d \n", args->numThread);
                    strcpy(args->file,argv[2]);
                    ProcessFile((void *)args);
                    FreeVars();
                    break;
                }
                else if(strcmp(argv[1],"-d") == 0){
                    InitializeVars(numThreads); //INITIALIZE VARS FOR THREADS
                    ReadDir(argv[2]);
                    for(int i = 0; i < maxThread; i++){
                        pthread_join(threads[i], NULL);
                    }
                    FreeVars();
                    break;
                }
                else{  
                    printf("ERROR INVALID NUMBER OF ARGUMENTS, EXAMPLE: \n \b -f file.p, -d directory -h threads\n");
                    break;
                }
                break;
            default: printf("ERROR: too many arguments.\nSyntax: %s [Input_file]\n\n", argv[0]);
        }

    free(threads);
    
    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("%f\n", elapsed_time);
    return 0;
}



void yyerror (yyscan_t scanner,int thread, const char *message) {
    pthread_mutex_lock(&writeFile_mutex);
    FILE *error = fopen("ERRORFILE.txt", "a");
    if(!error){
        perror("ERROR: Cant create ERRORFILE.txt");
        pthread_mutex_unlock(&writeFile_mutex);
        exit(EXIT_FAILURE);
    }
    ScanVars *vars = (ScanVars *) yyget_extra(scanner);

    fprintf (error, "%s \tFILE: %s \tLINE: \t%d TIME: %s\r\n", message, vars->fileName, yyget_lineno(scanner), asctime(timeinfo));

    fclose(error); 
    pthread_mutex_unlock(&writeFile_mutex);

    printf("CHECK ERRORFILE!!!!!\n");
       
    }
