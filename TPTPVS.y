%{
#define _GNU_SOURCE    
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
            return "i";
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


%}


%define parse.error verbose
%define api.pure full

%union{
    int valInt;
    char *valChar; 
}
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param{ int thread }


%token OPAREN CPAREN OBRA CBRA OKEY CKEY COMMA DOT DDOT
%token THF TFF
%token AXIOM HYPOTHESIS DEFINITION LEMMA THEOREM CONJECTURE NEGATEDCONJ TYPE ASSUMPTION PLAIN UNKNOWN
%token EQUAL_COMB DESCRIPTION_COMB CHOICE_COMB EXISTS_COMB FORALL_COMB
%token DESCRIPTION CHOICE LAMBDA EXISTS FORALL GENTZ_ARROW ARROW  %left VLINE %left AND %left APPLICATION 
%token UNARY_CONNECTIVE ASSIGNMENT IMPLIES IFF INFIX_EQUALITY INFIX_INEQUALITY SUBTYPE_SIGN
%token NIFF NOR NAND
%token TYPED_EXISTS TYPED_FORALL
%token LET LET1 LET2 DOLLAR_COND INCLUDE_HEADER
%token PLUS STAR 

%token <valChar> VAR DOLLAR_WORD FUNCTOR DISTINCT_OBJECT NUMBER SYSTEM_CONSTANT COMMENT INCLUDE_FILE DIV MULTIBLOCK

%type <valChar> thf_annotated
%type <valChar> thf_xprod_type thf_unitary_type thf_unitary_formula thf_atom thf_function thf_quantifier thf_pair_connective thf_quantified_formula thf_unary_formula thf_conditional
%type <valChar> thf_let thf_tuple thf_unary_connective thf_logic_formula thf_formula_list thf_sequent thf_union_type thf_mapping_type thf_binary_type thf_apply_type thf_apply_formula
%type <valChar> thf_top_level_type thf_subtype thf_typeable_formula thf_arguments thf_formula thf_typed_variable thf_variable thf_variable_list thf_quantification thf_and_formula
%type <valChar> thf_or_formula thf_conn_term thf_binary_tuple thf_binary_pair thf_type_formula thf_binary_formula annotated_formula tptp_file tptp_input

%type <valChar> fof_quantifier th0_quantifier th1_quantifier th1_unary_connective

%type <valChar> binary_connective atom untyped_atom constant defined_term type assoc_connective

%type <valChar> comments  include_file id

%start S

%%
S: tptp_file {                  FILE *out = yyget_out(scanner);
                                fprintf(out,"%c--Creation-Date: %s", 37, asctime(timeinfo));
                                fprintf(out,"%c--From-File: %s\n", 37, fileName[thread]);
                                if(auxComment[thread] != NULL){
                                    fprintf(out,"%s\n", auxComment[thread]);
                                }
                                fprintf(out,"%s : THEORY \n \tBEGIN\n", fileName[thread]);
                                if(existTypePlus[thread]){
                                    fprintf(out,"\ni : TYPE+ \n");
                                }
                                fprintf(out,"\n%s", $1);
                                fprintf(out,"\n\tEND %s",fileName[thread]);

                                free($1);
                                free(aux[thread]);
                                free(auxComment[thread]);
                                free(fileName[thread]);
                                free(auxVar[thread]);
            }
    ;

tptp_file: tptp_input tptp_file {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($2) + 5);
                                    snprintf(aux[thread], strlen($1) + strlen($2) + 5,"%s%s",$1, $2);
                                    $$ = strdup(aux[thread]); free($1); free($2);}
    | tptp_input {$$ = strdup($1);  free($1);}
    ;

tptp_input: annotated_formula {$$ = strdup($1);  free($1); //PARSE FORMULAS
                            }
    | INCLUDE_HEADER OPAREN include_file CPAREN DOT { free(aux[thread]); aux[thread] = malloc(strlen($3) + 20); //PARSE INCLUDEES
                                    snprintf(aux[thread], strlen($3) + 20,"\ninclude %s",$3);
                                    $$ = strdup(aux[thread]); free($3);
                                }
    | comments { //WE PARSE COMMENTS
                    if(auxComment[thread] == NULL){
                        auxComment[thread] = strdup($1);
                        }
                    else{
                        char *temp;
                        asprintf(&temp, "%s%s", auxComment[thread], $1);
                        free(auxComment[thread]);
                        auxComment[thread] = strdup(temp);
                        free(temp);
                        }
                 $$ = strdup("");
                 free($1);
                 }
	;

include_file: INCLUDE_FILE {$$ = strdup($1);  free($1);} //we can use this for name list includes
    ;

comments: DIV { free(aux[thread]); aux[thread] = malloc(15 + strlen($1));
                                    snprintf(aux[thread],15 + strlen($1),"%s\n", $1);
                                    $$ = strdup(aux[thread]);
                                    free($1);
                            }
        | MULTIBLOCK { free(aux[thread]); aux[thread] = malloc(15 + strlen($1));
                                    snprintf(aux[thread],15 + strlen($1),"%s\n", $1);
                                    $$ = strdup(aux[thread]);
                                    free($1);
                    }
    ;

annotated_formula: thf_annotated {$$ = strdup($1);  free($1);}
//	| tff_annotated  {if(strcmp($1,"")) $$ = strdup($1);
//                                    else $$ = strdup("");}
//	| fof_annotated
//	| cnf_annotated
	;

thf_annotated: THF OPAREN id COMMA type COMMA thf_formula CPAREN DOT {if(strcmp($5,"TYPE") == 0){ //we use a TAG for python script
                                                                            free(aux[thread]);
                                                                            aux[thread] = malloc(strlen(auxVar[thread]) + strlen($7) + 25);
                                                                            snprintf(aux[thread],strlen(auxVar[thread]) + strlen($7) + 25,"!DT¡ %s\n", $7);
                                                                            $$ = strdup(aux[thread]);  free($3); free($5); free($7);
                                                                            }
                                                                            else if(strcmp($5,"DEFINITION") == 0){ //we use a TAG for python script
                                                                                free(aux[thread]); aux[thread] = malloc(strlen($7) + 20); 
                                                                                snprintf(aux[thread], strlen($7) + 20,"!DEF¡ %s \n", $7);
                                                                                $$ = strdup(aux[thread]); free($3); free($5); free($7);
                                                                            }
                                                                            /*else if(Ends_AnthemDef($3)){ //we use a TAG for python script
                                                                                free(aux[thread]); aux[thread] = malloc(strlen($7) + 20); 
                                                                                snprintf(aux[thread], strlen($7) + 20,"!DEF¡ %s \n", $7);
                                                                                $$ = strdup(aux[thread]); free($7); free($3); free($5);
                                                                            }*/
                                                                           else{
                                                                                free(aux[thread]); 
                                                                                aux[thread] = malloc(strlen($3) + strlen($5) + strlen($7) + 20); //Direct parse
                                                                                snprintf(aux[thread], strlen($3) + strlen($5) + strlen($7) + 20,"\n\n%s : %s \n \t%s \n", $3, $5, $7);
                                                                                $$ = strdup(aux[thread]); free($3); free($5); free($7);
                                                                            }
                                                                        }
	;

id : NUMBER {$$ = strdup($1); free($1);/* id formula "number" */}
    | FUNCTOR {$$ = strdup($1); free($1);/* id formula "functor" */}
    | type {free(aux[thread]); aux[thread] = malloc(strlen($1) + 20); 
                snprintf(aux[thread], strlen($1) + 20,"%s%d", $1, count++);
                $$ = strdup(aux[thread]); free($1);}
;

/*tff_annotated: TFF OPAREN FUNCTOR COMMA type COMMA tff_formula CPAREN DOT {if(strcmp($5,"TYPE") == 0){
                                                                           Add_Variable(&head,$7,$5);
                                                                            $$ = strdup("");
                                                                           }
                                                                         else{
                                                                              snprintf(aux,sizeof(aux),"\n%s : %s \n \t%s \n", $3, $5, $7);
                                                                               $$ = strdup(aux); printf("%s",aux);}}
	| TFF OPAREN NUMBER COMMA type COMMA tff_formula CPAREN DOT {if(strcmp($5,"TYPE") == 0){
                                                                            Add_Variable(&head,$7,$5);
                                                                            $$ = strdup("");
                                                                            }
                                                                           else{
                                                                                snprintf(aux,sizeof(aux),"\n%s : %s \n \t%s \n", $3, $5, $7);
                                                                                $$ = strdup(aux);}}
    ;
*/
//fof_annotated: FOF OPAREN NAME COMMA type COMMA fof_formula CPAREN
//	;

//cnf_annotated: CNF OPAREN NAME COMMA type COMMA cnf_formula CPAREN
//	;

type: AXIOM {$$ = strdup("AXIOM"); /* convert bottom of the tree to PVS syntax */}
	| HYPOTHESIS {$$ = strdup("ASSUME");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
	| DEFINITION {$$ = strdup("DEFINITION");  /* convert bottom of the tree to PVS syntax */}
	| LEMMA {$$ = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax */}
	| THEOREM {$$ = strdup("THEOREM");  /* convert bottom of the tree to PVS syntax */}
	| CONJECTURE {$$ = strdup("CONJECTURE");  /* convert bottom of the tree to PVS syntax */}
	| NEGATEDCONJ {$$ = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
	| TYPE {$$ = strdup("TYPE");  /* convert bottom of the tree to PVS syntax */}
	| ASSUMPTION {$$ = strdup("AXIOM");  /* convert bottom of the tree to PVS syntax  --WARNING - NOT DIRECT CONVERSION-- */}
	| PLAIN {$$ = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
	| UNKNOWN {$$ = strdup("LEMMA");  /* convert bottom of the tree to PVS syntax --WARNING - NOT DIRECT CONVERSION-- */}
	;

thf_formula: thf_logic_formula {$$ = strdup($1); free($1);/* char comes from thf_logic_formula*/}
	| thf_sequent {$$ = strdup($1); free($1);/* char comes from thf_sequent*/}
	;


thf_logic_formula: thf_binary_formula {$$ = strdup($1); free($1);/* char comes from thf_binary_formula*/}
    | thf_unitary_formula { $$ = strdup($1); free($1);/* char comes from thf_unitary_formula*/}
    | thf_type_formula {$$ = strdup($1); free($1);/* char comes from type_formula*/}
    | thf_subtype {$$ = strdup($1); free($1);/* char comes from subtype*/}
    ;

thf_binary_formula: thf_logic_formula binary_connective thf_logic_formula {free(aux[thread]); aux[thread] = malloc(strlen($1)+ strlen($2) + strlen($3) + 5); 
                                                                                    snprintf(aux[thread], strlen($1)+ strlen($2) + strlen($3) + 5,"%s %s %s ", $1, $2, $3);
                                                                                    $$ = strdup(aux[thread]); free($1); free($2); free($3);  /*we parser base formula */ }
    | thf_logic_formula assoc_connective thf_logic_formula {free(aux[thread]); aux[thread] = malloc(strlen($1)+ strlen($2) + strlen($3) + 5); 
                                                                                    snprintf(aux[thread], strlen($1)+ strlen($2) + strlen($3) + 5,"%s %s %s ", $1, $2, $3);
                                                                                    $$ = strdup(aux[thread]); free($1); free($2); free($3);  /*we parser base formula */ } 

    | thf_binary_pair {$$ = strdup($1); free($1);/*sending up the pair */}
	| thf_binary_tuple {$$ = strdup($1); free($1);/*sending up the tuple */}
	| thf_binary_type {$$ = strdup($1); free($1);/*sending up the tuple */}
	;

thf_binary_pair: thf_unitary_formula thf_pair_connective thf_unitary_formula {  if(strcmp($2,"!=") == 0){
                                                                                    free(aux[thread]); aux[thread] = malloc(strlen($1)+ strlen($2) + strlen($3) + 15); 
                                                                                    snprintf(aux[thread], strlen($1)+ strlen($2) + strlen($3) + 15,"NOT(%s = %s) ", $1, $3);
                                                                                    $$ = strdup(aux[thread]); free($1); free($2); free($3);  /*we parser base formula */
                                                                                }   
                                                                                else{
                                                                                    free(aux[thread]); aux[thread] = malloc(strlen($1)+ strlen($2) + strlen($3) + 5); 
                                                                                    snprintf(aux[thread], strlen($1)+ strlen($2) + strlen($3) + 5,"%s %s %s ", $1, $2, $3);
                                                                                    $$ = strdup(aux[thread]); free($1); free($2); free($3);  /*we parser base formula */
                                                                                }
                                                                            }

    ;

thf_binary_tuple: thf_or_formula {$$ = strdup($1); free($1);/* sending up the OR formula*/}
    | thf_and_formula {$$ = strdup($1); free($1);/* sending up the AND formula*/}
    | thf_apply_formula {$$ = strdup($1); free($1);/* sending up the apply formula*/}
    ;

thf_or_formula: thf_unitary_formula VLINE thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 15); 
                                                                    snprintf(aux[thread],strlen($1) + strlen($3) + 15,"%s OR %s ", $1, $3);
                                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser base formula */}
	| thf_or_formula VLINE thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 15); 
                                                    snprintf(aux[thread],strlen($1) + strlen($3) + 15,"%s OR %s", $1, $3);
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser base formula */}
	;

thf_and_formula: thf_unitary_formula AND thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 15); 
                                                                snprintf(aux[thread],strlen($1) + strlen($3) + 15,"%s AND %s ", $1, $3);
                                                                $$ = strdup(aux[thread]); free($1); free($3);/*we parser base formula */}
    | thf_and_formula AND thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 15);  
                                                    snprintf(aux[thread],strlen($1) + strlen($3) + 15,"%s AND %s ", $1, $3);
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser compose formula */}
    ;

thf_apply_formula: thf_unitary_formula APPLICATION thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                                            snprintf(aux[thread],strlen($1) + strlen($3) + 5," %s(%s) ", $1, $3);
                                                                            $$ = strdup(aux[thread]); free($1); free($3);/*we parser base formula */}
    | thf_apply_formula APPLICATION thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5," %s(%s) ", $1, $3);
                                                                $$ = strdup(aux[thread]); free($1); free($3);/*we parser compose formula */}
    ;

thf_unitary_formula: thf_quantified_formula {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_unary_formula {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_atom {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_conditional {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_let {$$ = strdup($1); free($1);/*sending up the let */}
    | thf_tuple {$$ = strdup($1); free($1);/*sending up the tuple */}
    | thf_unitary_formula INFIX_EQUALITY thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1)+ strlen($3) + 15);
                                        snprintf(aux[thread],strlen($1)+ strlen($3) + 15,"%s = %s",$1, $3);
                                        $$ = strdup(aux[thread]); free($1); free($3);/*sending up the tuple */}

    | thf_unitary_formula INFIX_INEQUALITY thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 25); 
                                                                snprintf(aux[thread], strlen($1) + strlen($3) + 25,"NOT(%s = %s) ", $1, $3);
                                                                $$ = strdup(aux[thread]); free($1); free($3);  /*we parser base formula */}
                                        
    | OPAREN thf_logic_formula CPAREN {free(aux[thread]); aux[thread] = malloc(strlen($2) + 5);
                                        snprintf(aux[thread],strlen($2) + 5,"(%s)", $2);
                                        $$ = strdup(aux[thread]); free($2);/*sending up the tuple */}
    ;



thf_quantified_formula: thf_quantification thf_unitary_formula {free(aux[thread]); 
                                                                    aux[thread] = malloc( strlen($1) + strlen($2) + 5); 
                                                                    snprintf(aux[thread], strlen($1) + strlen($2) + 5,"%s %s ", $1, $2);
                                                                    $$ = strdup(aux[thread]); free($1); free($2);/*we parser quantification formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_quantification: thf_quantifier OBRA thf_variable_list CBRA DDOT {free(aux[thread]);
                                                                        aux[thread] = malloc(strlen($1) + strlen($3) + 10);
                                                                        snprintf(aux[thread], strlen($1) + strlen($3) + 10,"%s (%s) : ", $1, $3);
                                                                        $$ = strdup(aux[thread]); free($1); free($3);/*we parser quantification head --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_variable_list: thf_variable COMMA thf_variable_list {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                            snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s , %s", $1, $3);
                                                            $$ = strdup(aux[thread]); free($1); free($3);/*we parser var list --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    | thf_variable {$$ = strdup($1); free($1);/*sending up the var */}
    ;

thf_variable: thf_typed_variable {$$ = strdup($1); free($1);/* convert bottom of the tree to PVS syntax */}
    | VAR {free(aux[thread]); aux[thread] = malloc(strlen($1)+ 15); 
                                                            snprintf(aux[thread], strlen($1) + 15,"%s: int", $1);
                                                            $$ = strdup(aux[thread]); free($1);/* convert bottom of the tree to PVS syntax */}
    ;

thf_typed_variable: VAR DDOT thf_top_level_type {free(auxVar[thread]); free(aux[thread]);
                                                aux[thread] = malloc(strlen($1) + strlen($3) + 5);
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s: %s", $1, Prepared_types($3, thread));/* Save the var for types name */
                                                auxVar[thread] = strdup($1); $$ = strdup(aux[thread]); free($1); free($3);
                                                /*sending up the var */}
    ;
/* AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIII*/
thf_unary_formula: thf_unary_connective thf_unitary_formula {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($2) + 5); 
                                                                            snprintf(aux[thread], strlen($1) + strlen($2) + 5,"%s %s", $1, $2);
                                                                            $$ = strdup(aux[thread]); free($1); free($2);/*we parser unary formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
                                                                            
    ;

thf_atom: thf_function {$$ = strdup($1); free($1);/*sending up the needed part of the term*/}
    | VAR {$$ = strdup($1); free($1);/*sending up the var */}
    | defined_term { $$ = strdup($1); free($1);/*sending up the needed part of the term*/}
    | thf_conn_term {free(aux[thread]); aux[thread] = malloc(strlen($1) + 5); 
                        snprintf(aux[thread], strlen($1) + 5,"(%s)", $1);
                        $$ = strdup(aux[thread]); free($1);/*sending up the needed part of the term*/}
    ;

thf_function: atom {$$ = strdup($1); free($1);/*we send up the atom*/}
    | FUNCTOR OPAREN thf_arguments CPAREN {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s (%s)",$1, $3); 
                                                $$ = strdup(aux[thread]); free($1); free($3);}
    | DOLLAR_WORD OPAREN thf_arguments CPAREN {if(strcmp($1,"$is_int") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"integer?(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp($1,"$is_rat") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"rational?(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp($1,"$abs") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"abs(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp($1,"$floor") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"floor(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp($1,"$ceiling") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"ceiling(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp($1,"$uminus") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"-%s", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else if(strcmp($1,"$distinct") == 0){free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5);
                                                    ParserArgs($3, $1);
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"NOT(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                else {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    ParserArgs($3, $1);
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"(%s)", $3); 
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */
                                                }
                                                }
    ;

thf_conn_term: thf_pair_connective {$$ = strdup($1); free($1); /*we send up the connective*/}
    | assoc_connective {$$ = strdup($1); free($1); /*we send up the connective*/}
    | thf_unary_connective {$$ = strdup($1); free($1); /*we send up the connective*/}
    ;

thf_conditional: DOLLAR_COND OPAREN thf_logic_formula COMMA thf_logic_formula COMMA thf_logic_formula CPAREN {free(aux[thread]); aux[thread] = malloc(strlen($3) + strlen($5) + strlen($7) + 25);
                                                                                                                snprintf(aux[thread], strlen($3) + strlen($5) + strlen($7) + 25,"IF (%s) THEN (%s) else (%s)", $3, $5, $7);
                                                                                                                $$ = strdup(aux[thread]); free($3); free($5); free($7);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_let: LET OPAREN thf_unitary_formula COMMA thf_formula CPAREN {free(aux[thread]); aux[thread] = malloc(strlen($3) + strlen($5) + 15);
                                                                    snprintf(aux[thread], strlen($3) + strlen($5) + 15 ,"let(%s) IN %s", $3, $5);
                                                                    $$ = strdup(aux[thread]); free($3); free($5); /*we parser let --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_arguments: thf_formula_list {$$ = strdup($1); free($1);/* we send up parsed formula_list */}
    ;

thf_type_formula: thf_typeable_formula DDOT thf_top_level_type {free(auxVar[thread]); free(aux[thread]);
                                                                aux[thread] = malloc(strlen($1) + strlen($3) + 5);
                                                                snprintf(aux[thread],strlen($1) + strlen($3) + 5,"%s: %s", $1, Prepared_types($3, thread));
                                                                auxVar[thread] = strdup($1); $$ = strdup(aux[thread]); free($1); free($3);}
    ;

thf_typeable_formula: thf_atom {$$ = strdup($1); free($1); /* convert bottom of the tree to PVS syntax */}
    | OPAREN thf_logic_formula CPAREN {free(aux[thread]); aux[thread] = malloc(strlen($2) + 5);
                                            snprintf(aux[thread], strlen($2) + 5,"(%s)", $2);
                                            $$ = strdup(aux[thread]); free($2);/*we parser types --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_subtype: thf_atom SUBTYPE_SIGN thf_atom {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s (SUBTYPE) %s", $1, $3);
                                                $$ = strdup(aux[thread]); free($1); free($3); /*we parser the subtype --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_top_level_type: thf_unitary_type {$$ = strdup($1); free($1);/* we send up the unitary type */}
    | thf_mapping_type {$$ = strdup($1); free($1);/* we send up the map type */}
    | thf_apply_type {$$ = strdup($1); free($1); /* we send up the apply type */}
    ;

thf_unitary_type: thf_unitary_formula {$$ = strdup($1);  free($1);/*store var name in $$*/ }
    ;

thf_apply_type: thf_apply_formula {$$ = strdup($1);  free($1);/* we send up the apply formula */}
    ;

thf_binary_type: thf_mapping_type { $$ = strdup($1); free($1); /* store in binary_type */ }
    | thf_xprod_type  { $$ = strdup($1); free($1); /* store in binary_type */ }
    | thf_union_type  { $$ = strdup($1); free($1);/* store in binary_type */ }
    ;
thf_mapping_type: thf_unitary_type ARROW thf_unitary_type {free(aux[thread]); 
                                                            aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                            snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s -> %s", $1, $3);
                                                            $$ = strdup(aux[thread]); free($1); free($3);/*we parser the arrow basic formula*/}
    | thf_unitary_type ARROW thf_mapping_type {free(aux[thread]); 
                                                aux[thread] = malloc(strlen($1) + strlen($3) + 5);
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s -> %s", $1, $3);
                                                $$ = strdup(aux[thread]); free($1); free($3);/*we parser the arrow compose formula*/}
    ;

thf_xprod_type: thf_unitary_type STAR thf_unitary_type {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5);
                                                            snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s * %s", $1, $3);
                                                            $$ = strdup(aux[thread]); free($1); free($3);/*we parser the star basic formula*/}
    | thf_xprod_type STAR thf_unitary_type {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s * %s", $1, $3);
                                                $$ = strdup(aux[thread]); free($1); free($3);/*we parser the star compose formula*/}
    ;

thf_union_type: thf_unitary_type PLUS thf_unitary_type { free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5);
                                                            snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s + %s", $1, $3);
                                                            $$ = strdup(aux[thread]); free($1); free($3);/*we parser the plus compose formula*/}
    | thf_union_type PLUS thf_unitary_type {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s + %s", $1, $3);
                                                $$ = strdup(aux[thread]); free($1); free($3); /*we parser the plus compose formula*/}
    ;

thf_sequent: thf_tuple GENTZ_ARROW thf_tuple {free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 20); 
                                                snprintf(aux[thread], strlen($1) + strlen($3) + 20,"%s IMPLIES(GENTZ) %s", $1, $3);
                                                $$ = strdup(aux[thread]); free($1); free($3); /*we parser the sequent implies*/}
    | OPAREN thf_sequent CPAREN {free(aux[thread]); aux[thread] = malloc(strlen($2) + 5); 
                                        snprintf(aux[thread],strlen($2) + 5,"(%s)", $2);
                                        $$ = strdup(aux[thread]); free($2); /*we parser the parenthesis sequent */}
    ;

thf_tuple: OBRA CBRA { $$ = strdup("[]"); /*we parser the empty bracket formula */}
    | OBRA thf_formula_list CBRA {free(aux[thread]); aux[thread] = malloc(strlen($2) + 5);
                                        snprintf(aux[thread],strlen($2) + 5,"[%s]", $2);
                                        $$ = strdup(aux[thread]); free($2); /*we parser the bracket formula */}
    | OKEY CKEY { $$ = strdup("{}"); /*we parser the empty braces formula */}
    | OKEY thf_formula_list CKEY { free(aux[thread]); aux[thread] = malloc(strlen($2) + 5); 
                                        snprintf(aux[thread],strlen($2) + 5,"{%s}", $2);
                                        $$ = strdup(aux[thread]); free($2);/*we parser the braces formula */}
    ;

thf_formula_list: thf_logic_formula {$$ = strdup($1); free($1);/* in this case we send directly the formula */}
    | thf_logic_formula COMMA thf_formula_list { free(aux[thread]); aux[thread] = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux[thread], strlen($1) + strlen($3) + 5,"%s , %s", $1, $3);
                                                    $$ = strdup(aux[thread]); free($1); free($3);/*we parser the , formula */}
    ;

thf_quantifier: fof_quantifier {$$ = strdup($1); free($1); /* we send up the saved token */}
    | th0_quantifier {$$ = strdup($1); free($1); /* we send up the saved token */}
    | th1_quantifier {$$ = strdup($1); free($1); /* we send up the saved token */}
    ; 

fof_quantifier: FORALL {$$ = strdup("FORALL "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    | EXISTS {$$ = strdup("EXISTS "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    ;

th0_quantifier: LAMBDA {$$ = strdup(" LAMBDA "); /* convert bottom of the tree to PVS syntax */}
    | CHOICE {$$ = strdup("APPLY"); /* convert bottom of the tree to PVS syntax */}
    | DESCRIPTION {$$ = strdup("APPLY"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    ;

th1_quantifier: TYPED_FORALL {$$ = strdup("FORALL "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    |   TYPED_EXISTS {$$ = strdup("EXISTS "); /* convert bottom of the tree to PVS syntax --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    ;

thf_pair_connective: INFIX_EQUALITY { $$ = strdup(" = "); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    | INFIX_INEQUALITY {$$ = strdup("!="); /* --WARNING - NOT DIRECT CONVERSION--*/}
    | binary_connective {$$ = strdup($1); free($1); /* we send up binary_connective Char */}
    | ASSIGNMENT { $$ = strdup(":"); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_unary_connective: UNARY_CONNECTIVE {{$$ = strdup("NOT"); /* convert bottom of the tree to PVS syntax */}}
    | th1_unary_connective {$$ = strdup($1); free($1); /**/}
    ;
th1_unary_connective: FORALL_COMB { $$ = strdup("FORALL"); /* bottom of the tree we save here the token*/}
    | EXISTS_COMB { $$ = strdup("EXISTS");/* bottom of the tree we save here the token*/}
    | CHOICE_COMB{ $$ = strdup("choice");/* bottom of the tree we save here the token*/}
    | DESCRIPTION_COMB { $$ = strdup("THE");/* bottom of the tree we save here the token*/}
    | EQUAL_COMB {$$ = strdup("=");/* bottom of the tree we save here the token*/ }
    ;

// LANGUAGE WORDS
atom: untyped_atom {$$ = strdup($1);  free($1); /*send up the functor*/}
    | DOLLAR_WORD {
        if (strcmp($1, "$true") == 0) {
            $$ = strdup("TRUE");
        } else if (strcmp($1, "$false") == 0) {
            $$ = strdup("FALSE");
        } else {
            $$ = strdup(Prepared_types($1, thread));
        }
        free($1); /* bottom of the tree we save here the token */}
    ;

untyped_atom: constant {$$ = strdup($1); free($1); /* we send up the FUNCTOR */}
    ;

constant: FUNCTOR {$$ = strdup($1); free($1); /*bottom of the tree we save here the token*/}
    ;

defined_term: NUMBER { $$ = strdup($1);  free($1); /*bottom of the tree we save here the token*/}
    | DISTINCT_OBJECT {$$ = strdup($1);   free($1);/*bottom of the tree we save here the token*/}
    ;

binary_connective: IFF {$$ = strdup(" IFF "); /*we convert the token to PVS*/}
    | IMPLIES {$$ = strdup(" IMPLIES "); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NIFF {$$ = strdup("NIFF"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NOR {$$ = strdup("NOR"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NAND {$$ = strdup("NAND"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    ;

assoc_connective: VLINE {$$ = strdup("OR"); /*bottom of the tree we save here the token*/}
    | AND {$$ = strdup("AND"); /*bottom of the tree we save here the token*/}
    
    ;

%%

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
            {
                FILE *in = stdin;
                InitializeVars(1);
                fileName[0] = strdup("TPTPS.pvs");
                ScanVars *scanVars = malloc(sizeof(ScanVars));
                scanVars->firstToken = 1;
                scanVars->fileName = strdup(fileName[0]);
                FILE *outputFile = fopen("Output/TPTPS.pvs", "w");
                if (outputFile == NULL) {
                    perror("ERROR: OutputFile cant be created.\n");
                    return 0;
                }
                head[0] = NULL;
                auxComment[0] = NULL;
                aux[0] = NULL;
                auxVar[0] = NULL;
                existType[0] = 0;
                existTypePlus[0] = 0;


                yyscan_t scanner;
                yylex_init_extra(scanVars, &scanner);
                yyset_out(outputFile, scanner);
                yyset_in(in, scanner);
                yyparse(scanner, 0);
                yylex_destroy(scanner);
                fclose(in);

                free(scanVars->fileName);
                fclose(outputFile);
                free(scanVars);
                FreeVars();
                break;
            }
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