%{
#include "structs.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

#ifdef _WIN32
    #define FILE_SEPARATOR '\\'
#else
    #define FILE_SEPARATOR '/'
#endif



extern int yylineno;
extern int yylex(void);
extern void yylex_destroy(void);
void yyerror (char const *);

int error = 0;
int count = 0;
int yylinenoLast = 1;
time_t rawtime;
struct tm * timeinfo;

Variable* head = NULL;

char *aux;
char *auxComment;
char *fileName;
char varDeclaration[528000];


char *Prepared_types(char *var){
    if(var != NULL) {
        if(!strcmp(var,"$int")){
            return "int";
        }
        else if(!strcmp(var,"$tType") | !strcmp(var,"$i")){
            return "TYPE";
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
            return var + 1;
        }
    }
    else
        return " ";

}

char *Prepare_ListVar() {
    Variable *temp = head;
    TypeGroup *typeHead = NULL;
    char result[2048] = "";
    
    strcpy(varDeclaration, "\n");
    while (temp != NULL) {
        if (VariableExistsInGroups(typeHead, temp->name)) {
            temp = temp->next;
            continue;
        }
        TypeGroup *tg = typeHead;
        while (tg) {
            if (strcmp(tg->type, temp->type) == 0) {
                if (strlen(tg->names) + strlen(temp->name) + 3 < sizeof(tg->names)) { 
                    strcat(tg->names, ", ");
                    strcat(tg->names, temp->name);
                }
                break;
            }
            tg = tg->next;
        }

        if (!tg) {
            TypeGroup *newGroup = (TypeGroup *)malloc(sizeof(TypeGroup));
            if (!newGroup) {
                while (typeHead) {
                    TypeGroup *toFree = typeHead;
                    typeHead = typeHead->next;
                    free(toFree);
                }
                return NULL;
            }
            strcpy(newGroup->type, temp->type);
            strcpy(newGroup->names, temp->name);
            newGroup->next = typeHead;
            typeHead = newGroup;
        }
        temp = temp->next;
    }
    TypeGroup *tg = typeHead;
    while (tg) {
        if (strlen(result) + strlen(tg->names) + strlen(tg->type) + 10 < sizeof(result)) { 
            strcat(result, tg->names);
            strcat(result, " : VAR ");
            strcat(result, tg->type);
            strcat(result, "\n");
        }

        TypeGroup *toFree = tg;
        tg = tg->next;
        free(toFree);
    }
    strcat(varDeclaration, result);
    strcat(varDeclaration, "\n");

    Free_Variables(head);
    return varDeclaration;
}





%}
%define parse.error verbose
%union{
    int valInt;
    char *valChar; 
}


%token OPAREN CPAREN OBRA CBRA OKEY CKEY COMMA DOT DDOT DIV OBLOCK CBLOCK
%token THF TFF
%token AXIOM HYPOTHESIS DEFINITION LEMMA THEOREM CONJECTURE NEGATEDCONJ TYPE ASSUMPTION PLAIN UNKNOWN
%token EQUAL_COMB DESCRIPTION_COMB CHOICE_COMB EXISTS_COMB FORALL_COMB
%token DESCRIPTION CHOICE LAMBDA EXISTS FORALL GENTZ_ARROW ARROW APPLICATION AND VLINE
%token UNARY_CONNECTIVE ASSIGNMENT IMPLIES IFF INFIX_EQUALITY INFIX_INEQUALITY SUBTYPE_SIGN
%token NIFF NOR NAND
%token TYPED_EXISTS TYPED_FORALL
%token LET LET1 LET2 DOLLAR_COND INCLUDE_HEADER
%token PLUS STAR 

%token <valChar> VAR DOLLAR_WORD FUNCTOR DISTINCT_OBJECT NUMBER SYSTEM_CONSTANT COMMENT INCLUDE_FILE

%type <valChar> thf_annotated
%type <valChar> thf_xprod_type thf_unitary_type thf_unitary_formula thf_atom thf_function thf_quantifier thf_pair_connective thf_quantified_formula thf_unary_formula thf_conditional
%type <valChar> thf_let thf_tuple thf_unary_connective thf_logic_formula thf_formula_list thf_sequent thf_union_type thf_mapping_type thf_binary_type thf_apply_type thf_apply_formula
%type <valChar> thf_top_level_type thf_subtype thf_typeable_formula thf_arguments thf_formula thf_typed_variable thf_variable thf_variable_list thf_quantification thf_and_formula
%type <valChar> thf_or_formula thf_conn_term thf_binary_tuple thf_binary_pair thf_type_formula thf_binary_formula annotated_formula tptp_file tptp_input

%type <valChar> fof_quantifier th0_quantifier th1_quantifier th1_unary_connective

%type <valChar> binary_connective atom untyped_atom constant defined_term type assoc_connective

%type <valChar> comments_text comments comment_atom include_file

%start S

%%
S: tptp_file {free(aux); aux = strdup(Prepare_ListVar());
                                printf("%c  Creation-Date: %s", 37, asctime(timeinfo));
                                printf("%c  From-File: %s\n", 37, fileName);
                                if(auxComment != NULL) printf("%s \n", auxComment);
                                    printf("%s : THEORY \n \tBEGIN", fileName);
                                    printf("\n%s",aux);
                                    printf("\n%s", $1);
                                    printf("\n\tEND %s",fileName);
                                    yylinenoLast = -1;
                                    free($1);
                                    free(auxComment);
                                             
            }
    ;

tptp_file: tptp_input tptp_file {free(aux); aux = malloc(strlen($1) + strlen($2) + 5);
                                    snprintf(aux, strlen($1) + strlen($2) + 5,"%s  %s",$1, $2);
                                    $$ = strdup(aux); free($1); free($2);}
    | tptp_input {$$ = strdup($1);  free($1);}
    ;

tptp_input: annotated_formula {$$ = strdup($1);  free($1); 
                                if(yylinenoLast == -1) yylinenoLast = yylineno;
                            }
    | INCLUDE_HEADER OPAREN include_file CPAREN DOT { free(aux); aux = malloc(strlen($3) + 20);
                                    snprintf(aux, strlen($3) + 20,"\ninclude %s",$3);
                                    $$ = strdup(aux); free($3);
                                }
    | comments { if(yylinenoLast == -1 | (yylineno - 2) <= yylinenoLast){
                    yylinenoLast = yylineno;
                    if(auxComment == NULL){
                        auxComment = strdup($1);
                        }
                    else{
                        char *temp;
                        asprintf(&temp, "%s%s", auxComment, $1);
                        free(auxComment);
                        auxComment = strdup(temp);
                        free(temp);
                        }
                    }
                 $$ = strdup("");
                 free($1);
                }
	;

include_file: INCLUDE_FILE {$$ = strdup($1);  free($1);}
    ;

comments: DIV {free(aux); aux = malloc(10);
                                    snprintf(aux,10,"%c\n",37);
                                    $$ = strdup(aux);
                            }
    
    | DIV comments_text {free(aux); aux = malloc(strlen($2) + 5);
                                    snprintf(aux,strlen($2) + 5,"%c %s\n",37, $2);
                                    $$ = strdup(aux);  free($2);
                            }
    | OBLOCK CBLOCK {free(aux); aux = malloc(10);
                                    snprintf(aux,10,"%c\n",37);
                                    $$ = strdup(aux);
                }
    | OBLOCK comments_text CBLOCK {free(aux); aux = malloc(strlen($2) + 5);
                                        snprintf(aux,strlen($2) + 5,"%c %s\n",37, $2);
                                        $$ = strdup(aux);  free($2);

                                }

    ;

comments_text: comments_text comment_atom  {free(aux); aux = malloc(strlen($1) + strlen($2) + 5);
                                                snprintf(aux,strlen($1) + strlen($2) + 5,"%s %s",$1, $2);
                                                $$ = strdup(aux);  free($1);  free($2);}
    | comment_atom {free(aux); aux = malloc(strlen($1) + 5);
                        snprintf(aux,strlen($1) + 5," %s ", $1);
                        $$ = strdup(aux);  free($1);}
    ;

comment_atom: VAR {$$ = strdup($1);  free($1);}
    | FUNCTOR {$$ = strdup($1);  free($1);}
    | DISTINCT_OBJECT { $$ = strdup($1);  free($1);}
    | NUMBER { $$ = strdup($1);  free($1);}
    | SYSTEM_CONSTANT { $$ = strdup($1);  free($1);}
    | COMMENT { $$ = strdup($1);  free($1);}
    | DDOT { $$ = strdup(":");}
    | DOT { $$ = strdup(".");}
    | LAMBDA {$$ = strdup("^");}
    | EXISTS {$$ = strdup("?");}
    | ARROW {$$ = strdup(">");}
    | OBRA {$$ = strdup("[");}
    | CBRA {$$ = strdup("]");}
    | CPAREN {$$ = strdup("(");}
    | OPAREN {$$ = strdup(")");}
    | AND {$$ = strdup("&");}
    | COMMA {$$ = strdup(",");}
    | VLINE {$$ = strdup("|");}
    | APPLICATION {$$ = strdup("@");}
    | IFF {$$ = strdup("<=>");}
    | IMPLIES {$$ = strdup("=>");}
    | INFIX_EQUALITY {$$ = strdup("=");}
    | INFIX_INEQUALITY {$$ = strdup("!=");}
    | NIFF {$$ = strdup("<~>");}
    | TYPE {$$ = strdup("type");}
    | CONJECTURE {$$ = strdup("conjecture");}
    | STAR {$$ = strdup("*");}
    | PLUS {$$ = strdup("+");}
    | SUBTYPE_SIGN {$$ = strdup(":>");}
    | FORALL {$$ = strdup("!");}
    ;

annotated_formula: thf_annotated {if(strcmp($1,"")){
                                     $$ = strdup($1);  free($1);
                                    }
                                    else{
                                         $$ = strdup("");  free($1);
                                        }
                                    }
//	| tff_annotated  {if(strcmp($1,"")) $$ = strdup($1);
//                                    else $$ = strdup("");}
//	| fof_annotated
//	| cnf_annotated
	;

thf_annotated: THF OPAREN FUNCTOR COMMA type COMMA thf_formula CPAREN DOT {if(strcmp($5,"TYPE") == 0){
                                                                            free(aux); aux = malloc(strlen($3) + strlen($7) + 20);
                                                                            snprintf(aux,strlen($3) + strlen($7) + 20,"\nDT %s: TYPE = [%s]\n", $3, $7);
                                                                            $$ = strdup(aux); free($5); free($7); free($3);
                                                                            }
                                                                            else if(strcmp($5,"DEFINITION") == 0){
                                                                                free(aux); aux = malloc(strlen($7) + 20); 
                                                                                snprintf(aux, strlen($7) + 20,"\nDEF %s \n", $7);
                                                                                $$ = strdup(aux); free($7); free($3); free($5);
                                                                            }
                                                                           else{
                                                                                free(aux); aux = malloc(strlen($3) + strlen($5) + strlen($7) + 20); 
                                                                                snprintf(aux, strlen($3) + strlen($5) + strlen($7) + 20,"\n%s : %s \n \t%s \n", $3, $5, $7);
                                                                                $$ = strdup(aux); free($3); free($5); free($7);
                                                                            }
                                                                        }
    | THF OPAREN NUMBER COMMA type COMMA thf_formula CPAREN DOT {if(strcmp($5,"TYPE") == 0){
                                                                            Add_Variable(&head,$7,$5);
                                                                            $$ = strdup("");  free($7);  free($5); free($3);
                                                                            }
                                                                           else{
                                                                                free(aux); aux = malloc(strlen($3) + strlen($5) + strlen($7) + 20); 
                                                                                snprintf(aux, strlen($3) + strlen($5) + strlen($7) + 20,"\n%s : %s \n \t%s \n", $3, $5, $7);
                                                                                $$ = strdup(aux); free($3); free($5); free($7);
                                                                            }
                                                                }
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

thf_binary_formula: thf_binary_pair {$$ = strdup($1); free($1);/*sending up the pair */}
	| thf_binary_tuple {$$ = strdup($1); free($1);/*sending up the tuple */}
	| thf_binary_type {$$ = strdup($1); free($1);/*sending up the tuple */}
	;

thf_binary_pair: thf_unitary_formula thf_pair_connective thf_unitary_formula {free(aux); aux = malloc(strlen($1)+ strlen($2) + strlen($3) + 5); 
                                                                                snprintf(aux, strlen($1)+ strlen($2) + strlen($3) + 5,"%s %s %s ", $1, $2, $3);
                                                                                $$ = strdup(aux); free($1); free($2); free($3);  /*we parser base formula */}
    ;

thf_binary_tuple: thf_or_formula {$$ = strdup($1); free($1);/* sending up the OR formula*/}
    | thf_and_formula {$$ = strdup($1); free($1);/* sending up the AND formula*/}
    | thf_apply_formula {$$ = strdup($1); free($1);/* sending up the apply formula*/}
    ;

thf_or_formula: thf_unitary_formula VLINE thf_unitary_formula {free(aux); aux = malloc(strlen($1) + strlen($3) + 15); 
                                                                    snprintf(aux,strlen($1) + strlen($3) + 15,"((%s) OR (%s)) ", $1, $3);
                                                                    $$ = strdup(aux); free($1); free($3);/*we parser base formula */}
	| thf_or_formula VLINE thf_unitary_formula {free(aux); aux = malloc(strlen($1) + strlen($3) + 15); 
                                                    snprintf(aux,strlen($1) + strlen($3) + 15,"((%s) OR (%s)) ", $1, $3);
                                                    $$ = strdup(aux); free($1); free($3);/*we parser base formula */}
	;

thf_and_formula: thf_unitary_formula AND thf_unitary_formula {free(aux); aux = malloc(strlen($1) + strlen($3) + 15); 
                                                                snprintf(aux,strlen($1) + strlen($3) + 15,"((%s) AND (%s)) ", $1, $3);
                                                                $$ = strdup(aux); free($1); free($3);/*we parser base formula */}
    | thf_and_formula AND thf_unitary_formula {free(aux); aux = malloc(strlen($1) + strlen($3) + 15);  
                                                    snprintf(aux,strlen($1) + strlen($3) + 15,"((%s) AND (%s)) ", $1, $3);
                                                    $$ = strdup(aux); free($1); free($3);/*we parser compose formula */}
    ;

thf_apply_formula: thf_unitary_formula APPLICATION thf_unitary_formula {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                                            snprintf(aux,strlen($1) + strlen($3) + 5," %s(%s) ", $1, $3);
                                                                            $$ = strdup(aux); free($1); free($3);/*we parser base formula */}
    | thf_apply_formula APPLICATION thf_unitary_formula {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                                snprintf(aux, strlen($1) + strlen($3) + 5," %s(%s) ", $1, $3);
                                                                $$ = strdup(aux); free($1); free($3);/*we parser compose formula */}
    ;

thf_unitary_formula: thf_quantified_formula {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_unary_formula {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_atom {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_conditional {$$ = strdup($1); free($1);/*sending up the formula */}
    | thf_let {$$ = strdup($1); free($1);/*sending up the let */}
    | thf_tuple {$$ = strdup($1); free($1);/*sending up the tuple */}
    | OPAREN thf_logic_formula CPAREN {free(aux); aux = malloc(strlen($2) + 5);
                                        snprintf(aux,strlen($2) + 5,"%s", $2);
                                        $$ = strdup(aux); free($2);/*sending up the tuple */}
    ;

thf_quantified_formula: thf_quantification thf_unitary_formula {free(aux); aux = malloc( strlen($1) + strlen($2) + 5); 
                                                                    snprintf(aux, strlen($1) + strlen($2) + 5,"%s %s ", $1, $2);
                                                                    $$ = strdup(aux); free($1); free($2);/*we parser quantification formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_quantification: thf_quantifier OBRA thf_variable_list CBRA DDOT {free(aux); aux = malloc(strlen($1) + strlen($3) + 10); 
                                                                        snprintf(aux, strlen($1) + strlen($3) + 10,"%s (%s) : ", $1, $3);
                                                                        $$ = strdup(aux); free($1); free($3);/*we parser quantification head --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_variable_list: thf_variable COMMA thf_variable_list {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                            snprintf(aux, strlen($1) + strlen($3) + 5,"%s , %s", $1, $3);
                                                            $$ = strdup(aux); free($1); free($3);/*we parser var list --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    | thf_variable {$$ = strdup($1); free($1);/*sending up the var */}
    ;

thf_variable: thf_typed_variable {$$ = strdup($1); free($1);/* convert bottom of the tree to PVS syntax */}
    | VAR {$$ = strdup($1); free($1);/* convert bottom of the tree to PVS syntax */}
    ;

thf_typed_variable: VAR DDOT thf_top_level_type {$$ = strdup($1);
                                                Add_Variable(&head, $1, $3); free($1); free($3);
                                                /*sending up the var */}
    ;

thf_unary_formula: thf_unary_connective OPAREN thf_logic_formula CPAREN {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                                            snprintf(aux, strlen($1) + strlen($3) + 5,"%s(%s)", $1, $3);
                                                                            $$ = strdup(aux); free($1); free($3);/*we parser unary formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_atom: thf_function {$$ = strdup($1); free($1);/*sending up the needed part of the term*/}
    | VAR {$$ = strdup($1); free($1);/*sending up the var */}
    | defined_term { $$ = strdup($1); free($1);/*sending up the needed part of the term*/}
    | thf_conn_term {free(aux); aux = malloc(strlen($1) + 5); 
                        snprintf(aux, strlen($1) + 5,"(%s)", $1);
                        $$ = strdup(aux); free($1);/*sending up the needed part of the term*/}
    ;

thf_function: atom {$$ = strdup($1); free($1);/*we send up the atom*/}
    | FUNCTOR OPAREN thf_arguments CPAREN {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux, strlen($1) + strlen($3) + 5,"%s (%s)",$1, $3); 
                                                $$ = strdup(aux); free($1); free($3);}
    | DOLLAR_WORD OPAREN thf_arguments CPAREN {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux, strlen($1) + strlen($3) + 5,"%s (%s)", Prepared_types($1), $3); 
                                                    $$ = strdup(aux); free($1); free($3);/*we send up the dollar_word (save arguments name 
                                                    in correct place)*/}
    ;

thf_conn_term: thf_pair_connective {$$ = strdup($1); free($1); /*we send up the connective*/}
    | assoc_connective {$$ = strdup($1); free($1); /*we send up the connective*/}
    | thf_unary_connective {$$ = strdup($1); free($1); /*we send up the connective*/}
    ;

thf_conditional: DOLLAR_COND OPAREN thf_logic_formula COMMA thf_logic_formula COMMA thf_logic_formula CPAREN {free(aux); aux = malloc(strlen($3) + strlen($5) + strlen($7) + 25);  
                                                                                                                snprintf(aux, strlen($3) + strlen($5) + strlen($7) + 25,"IF (%s) THEN (%s) else (%s)", $3, $5, $7);
                                                                                                                $$ = strdup(aux); free($3); free($5); free($7);/*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_let: LET OPAREN thf_unitary_formula COMMA thf_formula CPAREN {free(aux); aux = malloc(strlen($3) + strlen($5) + 15);  
                                                                    snprintf(aux, strlen($3) + strlen($5) + 15 ,"let(%s) IN %s", $3, $5);
                                                                    $$ = strdup(aux); free($3); free($5); /*we parser let --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_arguments: thf_formula_list {$$ = strdup($1); free($1);/* we send up parsed formula_list */}
    ;

thf_type_formula: thf_typeable_formula DDOT thf_top_level_type {$$ = strdup($1); /*we send up the name */
                                                                /* we store the var for PVS file*/
                                                                Add_Variable(&head, $1, $3); free($1); free($3);}
    ;

thf_typeable_formula: thf_atom {$$ = strdup($1); free($1); /* convert bottom of the tree to PVS syntax */}
    | OPAREN thf_logic_formula CPAREN {free(aux); aux = malloc(strlen($2) + 5);
                                            snprintf(aux, strlen($2) + 5,"(%s)", $2);
                                            $$ = strdup(aux); free($2);  /*we parser types --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_subtype: thf_atom SUBTYPE_SIGN thf_atom {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux, strlen($1) + strlen($3) + 5,"%s: > %s", $1, $3);
                                                $$ = strdup(aux); free($1); free($3); /*we parser the subtype --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
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
thf_mapping_type: thf_unitary_type ARROW thf_unitary_type {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                            snprintf(aux, strlen($1) + strlen($3) + 5,"%s -> %s", $1, $3);
                                                            $$ = strdup(aux); free($1); free($3);/*we parser the arrow basic formula*/}
    | thf_unitary_type ARROW thf_mapping_type {free(aux); aux = malloc(strlen($1) + strlen($3) + 5);  
                                                snprintf(aux, strlen($1) + strlen($3) + 5,"%s -> %s", $1, $3);
                                                $$ = strdup(aux); free($1); free($3);/*we parser the arrow compose formula*/}
    ;

thf_xprod_type: thf_unitary_type STAR thf_unitary_type {free(aux); aux = malloc(strlen($1) + strlen($3) + 5);  
                                                            snprintf(aux, strlen($1) + strlen($3) + 5,"%s * %s", $1, $3);
                                                            $$ = strdup(aux); free($1); free($3);/*we parser the star basic formula*/}
    | thf_xprod_type STAR thf_unitary_type {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux, strlen($1) + strlen($3) + 5,"%s * %s", $1, $3);
                                                $$ = strdup(aux); free($1); free($3);/*we parser the star compose formula*/}
    ;

thf_union_type: thf_unitary_type PLUS thf_unitary_type { free(aux); aux = malloc(strlen($1) + strlen($3) + 5);
                                                            snprintf(aux, strlen($1) + strlen($3) + 5,"%s + %s", $1, $3);
                                                            $$ = strdup(aux); free($1); free($3);/*we parser the plus compose formula*/}
    | thf_union_type PLUS thf_unitary_type {free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                snprintf(aux, strlen($1) + strlen($3) + 5,"%s + %s", $1, $3);
                                                $$ = strdup(aux); free($1); free($3); /*we parser the plus compose formula*/}
    ;

thf_sequent: thf_tuple GENTZ_ARROW thf_tuple {free(aux); aux = malloc(strlen($1) + strlen($3) + 20); 
                                                snprintf(aux, strlen($1) + strlen($3) + 20,"%s IMPLIES(GENTZ) %s", $1, $3);
                                                $$ = strdup(aux); free($1); free($3); /*we parser the sequent implies*/}
    | OPAREN thf_sequent CPAREN {free(aux); aux = malloc(strlen($2) + 5); 
                                        snprintf(aux,strlen($2) + 5,"(%s)", $2);
                                        $$ = strdup(aux); free($2); /*we parser the parenthesis sequent */}
    ;

thf_tuple: OBRA CBRA { $$ = strdup("[]"); /*we parser the empty bracket formula */}
    | OBRA thf_formula_list CBRA {free(aux); aux = malloc(strlen($2) + 5);  
                                        snprintf(aux,strlen($2) + 5,"[%s]", $2);
                                        $$ = strdup(aux); free($2); /*we parser the bracket  formula */}
    | OKEY CKEY { $$ = strdup("{}"); /*we parser the empty braces formula */}
    | OKEY thf_formula_list CKEY { free(aux); aux = malloc(strlen($2) + 5); 
                                        snprintf(aux,strlen($2) + 5,"{%s}", $2);
                                        $$ = strdup(aux); free($2);/*we parser the braces formula */}
    ;

thf_formula_list: thf_logic_formula {$$ = strdup($1); free($1);/* in this case we send directly the formula */}
    | thf_logic_formula COMMA thf_formula_list { free(aux); aux = malloc(strlen($1) + strlen($3) + 5); 
                                                    snprintf(aux, strlen($1) + strlen($3) + 5,"%s , %s", $1, $3);
                                                    $$ = strdup(aux); free($1); free($3);/*we parser the , formula */}
    ;

thf_quantifier: fof_quantifier {$$ = strdup($1); free($1); /* we send up the saved token */}
    | th0_quantifier {$$ = strdup($1); free($1); /* we send up the saved token */}
    | th1_quantifier {$$ = strdup($1); free($1); /* we send up the saved token */}
    ; 

fof_quantifier: FORALL {$$ = strdup("FORALL "); /* convert bottom of the tree to PVS syntax  --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    | EXISTS {$$ = strdup("EXISTS "); /* convert bottom of the tree to PVS syntax  --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    ;

th0_quantifier: LAMBDA {$$ = strdup(" LAMBDA "); /* convert bottom of the tree to PVS syntax */}
    | CHOICE {$$ = strdup("APPLY"); /* convert bottom of the tree to PVS syntax */}
    | DESCRIPTION {$$ = strdup("APPLY"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    ;

th1_quantifier: TYPED_FORALL {$$ = strdup("FORALL "); /* convert bottom of the tree to PVS syntax  --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    |   TYPED_EXISTS  {$$ = strdup("EXISTS "); /* convert bottom of the tree to PVS syntax  --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?--*/}
    ;

thf_pair_connective: INFIX_EQUALITY {$$ = strdup(" = "); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    | INFIX_INEQUALITY {$$ = strdup("!="); /* --WARNING - NOT DIRECT CONVERSION--  */}
    | binary_connective {$$ = strdup($1); free($1); /* we send up binary_connective Char */}
    | ASSIGNMENT { $$ = strdup(":"); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_unary_connective: UNARY_CONNECTIVE {{$$ = strdup("HOLA"); /* convert bottom of the tree to PVS syntax */}}
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
    | DOLLAR_WORD {$$ = strdup(Prepared_types($1));  free($1); /* bottom of the tree we save here the token*/}
    ;

untyped_atom: constant {$$ = strdup($1); free($1); /* we send up the FUNCTOR */}
    ;

constant: FUNCTOR {$$ = strdup($1); free($1); /*bottom of the tree we save here the token*/}
    ;

defined_term: NUMBER { $$ = strdup($1);  free($1); /*bottom of the tree we save here the token*/}
    | DISTINCT_OBJECT {$$ = strdup($1);   free($1);/*bottom of the tree we save here the token*/}
    ;

binary_connective: IFF {$$ = strdup(" = "); /*we convert the token to PVS*/}
    | IMPLIES {$$ = strdup(" IMPLIES "); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NIFF {$$ = strdup("NIFF"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NOR {$$ = strdup("NOR"); /* --WARNING - NOT DIRECT CONVERSION--  */}
    | NAND {$$ = strdup("NAND"); /* --WARNING - NOT DIRECT CONVERSION--  */}
    ;

assoc_connective: VLINE {$$ = strdup("OR"); /*bottom of the tree we save here the token*/}
    | AND {$$ = strdup("AND"); /*bottom of the tree we save here the token*/}
    ;

%%

void ProcessFile(char *file, FILE **yyin){
    FILE *outputFile;
    char outputFileName [1024];
    char command[2048];
    struct stat st = {0};

    if (stat("Output", &st) == -1) {
            mkdir("Output", 0700); 
        }
   *yyin = fopen(file, "r");
        if (*yyin == NULL) {
            printf("ERROR: File cant be opened.\r\n");
        }
        else {
            char *baseName = strrchr(file, FILE_SEPARATOR);
            if (baseName) {
                baseName++;
            } else {
                baseName = file;
            }
            
            snprintf(outputFileName,sizeof(outputFileName)+4, "Output%c%s.pvs", FILE_SEPARATOR, baseName);
            fileName = strdup(baseName);
            outputFile = freopen(outputFileName, "w", stdout);
            if (outputFile == NULL) {
                printf("ERROR: OutputFile cant be created.\n");
                fclose(*yyin);
                return;
            }
            yyparse();
            fclose(outputFile);
            free(fileName);
            fclose(*yyin);
            yylex_destroy();
        }

    freopen("/dev/tty", "w", stdout);
    snprintf(command, sizeof(command), "python3 parser.py %s", outputFileName);
    system(command);
} 

int main(int argc, char *argv[]) {
    extern FILE *yyin;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

        switch (argc) {
            case 1:	
                yyin=stdin;
                fileName = strdup("EXAMPLE.pvs");
                yyparse();
                free(fileName);
                yylex_destroy();
                break;
            case 2: 
                printf("ERROR INVALID NUMBER OF ARGUMENTS, EXAMPLE: \n \b -f file.p, -d directory");
                break;
            case 3: 
                if(strcmp(argv[1],"-f") == 0){
                    ProcessFile(argv[2], &yyin);
                    break;
                }
                else if(strcmp(argv[1],"-d") == 0){
                    struct dirent *de;
                    DIR *dr = opendir(argv[2]);
                    char fullPath[1024];
                    if (dr == NULL){ 
                        printf("Could not open current directory" ); 
                        break;
                    }
                    while ((de = readdir(dr)) != NULL){
                        if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0){
                            snprintf(fullPath, sizeof(fullPath), "%s/%s", argv[2], de->d_name);
                            head = NULL;
                            auxComment = NULL;
                            ProcessFile(fullPath, &yyin);
                        }
                    }
                    closedir(dr);
                    break;
                }
                else{  
                    printf("ERROR INVALID NUMBER OF ARGUMENTS, EXAMPLE: \n \b -f file.p, -d directory");
                    break;
                }
                break;
            default: printf("ERROR: too many arguments.\nSyntax: %s [Input_file]\n\n", argv[0]);
        }
        free(aux);
        return 0;
}



void yyerror (char const *message) { fprintf (stderr, "%s\r\n", message);}