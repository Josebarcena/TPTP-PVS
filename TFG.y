%{
#include "structs.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int yylineno;
extern int yylex(void);
void yyerror (char const *);

int error = 0;
int count = 0;
Variable* head = NULL;

char aux[4000];


char *Prepared_types(char *type){
    if(!strcmp(type,"$int")){
        return "int";
    }
    else{
        return "bool";
    }
}

char *Prepare_ListVar(){
    char *varDeclaration = malloc(2048);
    Variable *temp = head;
    strcpy(varDeclaration,"\%-----VARs------- \n");
    while(temp != NULL)
    {
        strcat(varDeclaration,temp->name);
        strcat(varDeclaration,temp->type);
        strcat(varDeclaration,"\n");
        temp = temp->next;
    }
    strcat(varDeclaration,"\%--------------- \n");
    return varDeclaration;
}

%}
%define parse.error verbose
%union{
	int valInt;
	float valFloat;
    char *valChar; 
}


%token OPAREN CPAREN OBRA CBRA OKEY CKEY COMMA DOT DDOT
%token THF
%token AXIOM HYPOTHESIS DEFINITION LEMMA THEOREM CONJECTURE NEGATEDCONJ TYPE ASSUMPTION PLAIN UNKNOWN
%token EQUAL_COMB DESCRIPTION_COMB CHOICE_COMB EXISTS_COMB FORALL_COMB
%token DESCRIPTION CHOICE LAMBDA EXISTS FORALL GENTZ_ARROW ARROW APPLICATION AND VLINE
%token UNARY_CONNECTIVE ASSIGNMENT IMPLIES IFF INFIX_EQUALITY INFIX_INEQUALITY SUBTYPE_SIGN
%token NIFF NOR NAND
%token TYPED_EXISTS TYPED_FORALL
%token LET DOLLAR_COND
%token PLUS STAR DIV

%token <valChar> VAR
%token <valChar> DOLLAR_WORD
%token <valChar> FUNCTOR
%token <valChar> DISTINCT_OBJECT
%token <valChar> NUMBER

%type <valChar> thf_xprod_type
%type <valChar> thf_unitary_type
%type <valChar> thf_unitary_formula
%type <valChar> thf_atom
%type <valChar> thf_function
%type <valChar> thf_quantifier
%type <valChar> thf_pair_connective
%type <valChar> thf_quantified_formula
%type <valChar> thf_unary_formula
%type <valChar> thf_conditional
%type <valChar> thf_let
%type <valChar> thf_tuple
%type <valChar> thf_unary_connective
%type <valChar> thf_logic_formula
%type <valChar> thf_formula_list
%type <valChar> thf_sequent
%type <valChar> thf_union_type
%type <valChar> thf_mapping_type
%type <valChar> thf_binary_type
%type <valChar> thf_apply_type
%type <valChar> thf_apply_formula
%type <valChar> thf_top_level_type
%type <valChar> thf_subtype
%type <valChar> thf_typeable_formula
%type <valChar> thf_arguments
%type <valChar> thf_formula
%type <valChar> thf_typed_variable
%type <valChar> thf_variable
%type <valChar> thf_variable_list
%type <valChar> thf_quantification
%type <valChar> thf_and_formula
%type <valChar> thf_or_formula
%type <valChar> thf_conn_term
%type <valChar> thf_binary_tuple 
%type <valChar> thf_binary_pair
%type <valChar> thf_type_formula
%type <valChar> thf_binary_formula

%type <valChar> fof_quantifier
%type <valChar> th0_quantifier
%type <valChar> th1_quantifier
%type <valChar> th1_unary_connective

%type <valChar> binary_connective
%type <valChar> atom
%type <valChar> untyped_atom
%type <valChar> constant
%type <valChar> defined_term
%type <valChar> type
%type <valChar> assoc_connective



%start S

%%
S: tptp_file {strcpy(aux,Prepare_ListVar()); printf("%s", aux);}
    ;

tptp_file: tptp_input tptp_file
    | tptp_input {printf("\n");}
    ;

tptp_input: annotated_formula {/*count++; printf("\n THF NUMBER: %d, ACCEPTED \n", count); */}//MISS INCLUDES 
//	| include
    | comments
	;
comments: DIV comments_right
    ;

comments_right: 
    ;

annotated_formula: thf_annotated
//	| tff_annotated
//	| fof_annotated
//	| cnf_annotated
	;

thf_annotated: THF OPAREN FUNCTOR COMMA type COMMA thf_formula CPAREN DOT {if(strcmp($5,"TYPE")) printf("%s : %s \n %s \n", $3, $5, $7);}
    | THF OPAREN NUMBER COMMA type COMMA thf_formula CPAREN DOT
	;

//tff_annotated: TFF OPAREN NAME COMMA type COMMA tff_formula CPAREN
//	;

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

thf_formula: thf_logic_formula {$$ = strdup($1); /* char comes from thf_logic_formula*/}
	| thf_sequent {$$ = strdup($1); /* char comes from thf_sequent*/}
	;


thf_logic_formula: thf_binary_formula {$$ = strdup($1); /* char comes from thf_binary_formula*/}
    | thf_unitary_formula {$$ = strdup($1); /* char comes from thf_unitary_formula*/}
    | thf_type_formula {$$ = strdup($1); /* char comes from type_formula*/}
    | thf_subtype {$$ = strdup($1); /* char comes from subtype*/}
    ;

thf_binary_formula: thf_binary_pair {$$ = strdup($1); /*sending up the pair */}
	| thf_binary_tuple {$$ = strdup($1); /*sending up the tuple */}
	| thf_binary_type {$$ = strdup($1); /*sending up the tuple */}
	;

thf_binary_pair: thf_unitary_formula thf_pair_connective thf_unitary_formula {snprintf(aux, sizeof(aux),"(%s %s %s) ", $1, $2, $3);
                                        $$ = strdup(aux); /*we parser base formula */}
    ;

thf_binary_tuple: thf_or_formula {$$ = strdup($1); /* sending up the OR formula*/}
    | thf_and_formula {$$ = strdup($1); /* sending up the AND formula*/}
    | thf_apply_formula {$$ = strdup($1); /* sending up the apply formula*/}
    ;

thf_or_formula: thf_unitary_formula VLINE thf_unitary_formula {snprintf(aux, sizeof(aux),"(%s) OR (%s) ", $1, $3);
                                        $$ = strdup(aux); /*we parser base formula */}
	| thf_or_formula VLINE thf_unitary_formula {snprintf(aux, sizeof(aux),"(%s) OR (%s) ", $1, $3);
                                        $$ = strdup(aux); /*we parser base formula */}
	;

thf_and_formula: thf_unitary_formula AND thf_unitary_formula {snprintf(aux, sizeof(aux),"(%s) AND (%s) ", $1, $3);
                                        $$ = strdup(aux); /*we parser base formula */}
    | thf_and_formula AND thf_unitary_formula {snprintf(aux, sizeof(aux),"(%s) AND (%s) ", $1, $3);
                                        $$ = strdup(aux); /*we parser compose formula */}
    ;

thf_apply_formula: thf_unitary_formula APPLICATION thf_unitary_formula {snprintf(aux, sizeof(aux)," %s(%s) ", $1, $3);
                                        $$ = strdup(aux); /*we parser base formula */}
    | thf_apply_formula APPLICATION thf_unitary_formula {snprintf(aux, sizeof(aux)," %s(%s) ", $1, $3);
                                        $$ = strdup(aux); /*we parser compose formula */}
    ;

/*AQUIIIII*/
thf_unitary_formula: thf_quantified_formula {$$ = strdup($1); /*sending up the formula */}
    | thf_unary_formula {$$ = strdup($1); /*sending up the formula */}
    | thf_atom {$$ = strdup($1); /*sending up the formula */}
    | thf_conditional {$$ = strdup($1); /*sending up the formula */}
    | thf_let {$$ = strdup($1); /*sending up the let */}
    | thf_tuple {$$ = strdup($1); /*sending up the tuple */}
    | OPAREN thf_logic_formula CPAREN {snprintf(aux, sizeof(aux),"(%s)", $2);
                                        $$ = strdup(aux); /*sending up the tuple */}
    ;

thf_quantified_formula: thf_quantification thf_unitary_formula {snprintf(aux, sizeof(aux),"%s (%s) ", $1, $2);
                                        $$ = strdup(aux); /*we parser quantification formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_quantification: thf_quantifier OBRA thf_variable_list CBRA DDOT {snprintf(aux, sizeof(aux),"%s (%s) : ", $1, $3);
                                        $$ = strdup(aux); /*we parser quantification head --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_variable_list: thf_variable COMMA thf_variable_list {snprintf(aux, sizeof(aux),"%s , %s", $1, $3);
                                        $$ = strdup(aux); /*we parser var list --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    | thf_variable {$$ = strdup($1); /*sending up the var */}
    ;

thf_variable: thf_typed_variable 
    | VAR {$$ = strdup($1); /* convert bottom of the tree to PVS syntax */}
    ;

thf_typed_variable: VAR DDOT thf_top_level_type {snprintf(aux,sizeof(aux),"%s : %s", $1, $3);
                                                    $$ = strdup(aux); /*sending up the var */}
    ;

thf_unary_formula: thf_unary_connective OPAREN thf_logic_formula CPAREN {snprintf(aux, sizeof(aux),"%s(%s)", $1, $3);
                                        $$ = strdup(aux); /*we parser unary formula --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_atom: thf_function {$$ = strdup($1); /*sending up the needed part of the term*/}
    | VAR {$$ = strdup($1); /*sending up the var */}
    | defined_term {$$ = strdup($1); /*sending up the needed part of the term*/}
    | thf_conn_term {$$ = strdup($1); /*sending up the needed part of the term*/}
    ;

thf_function: atom {$$ = strdup($1); /*we send up the atom*/}
    | FUNCTOR OPAREN thf_arguments CPAREN {$$ = strdup(Prepared_types($1)); /*we send the functor (save arguments name 
                                                    in correct place)*/}
    | DOLLAR_WORD OPAREN thf_arguments CPAREN {$$ = strdup($1); /*we send up the dollar_word (save arguments name 
                                                    in correct place)*/}
    ;

thf_conn_term: thf_pair_connective {$$ = strdup($1); /*we send up the connective*/}
    | assoc_connective {$$ = strdup($1); /*we send up the connective*/}
    | thf_unary_connective {$$ = strdup($1); /*we send up the connective*/}
    ;

thf_conditional: DOLLAR_COND OPAREN thf_logic_formula COMMA thf_logic_formula COMMA thf_logic_formula CPAREN {snprintf(aux, sizeof(aux),"IF (%s) THEN (%s) else (%s)", $3, $5, $7);
                                        $$ = strdup(aux); /*we parser IF THEN ELSE --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_let: LET OPAREN thf_unitary_formula COMMA thf_formula CPAREN {snprintf(aux, sizeof(aux),"let(%s) IN %s", $3, $5);
                                        $$ = strdup(aux); /*we parser let --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_arguments: thf_formula_list {$$ = strdup($1); /* we send up parsed formula_list */}
    ;

thf_type_formula: thf_typeable_formula DDOT thf_top_level_type {$$ = strdup($1); /*we send up the name */
                                                                /* we store the var for PVS file*/
                                                                Add_Variable(&head, $1, $3);}
    ;

thf_typeable_formula: thf_atom
    | OPAREN thf_logic_formula CPAREN {snprintf(aux, sizeof(aux),"(%s)", $2);
                                        $$ = strdup(aux); /*we parser types --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_subtype: thf_atom SUBTYPE_SIGN thf_atom { snprintf(aux, sizeof(aux),"%s: > %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the subtype --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_top_level_type: thf_unitary_type {$$ = $1;/* we send up the unitary type */}
    | thf_mapping_type {$$ = $1;/* we send up the map type */}
    | thf_apply_type {$$ = $1; /* we send up the apply type */}
    ;

thf_unitary_type: thf_unitary_formula {$$ = strdup($1); /*store var name in $$*/ }
    ;

thf_apply_type: thf_apply_formula {$$ = strdup($1); /* we send up the apply formula */}
    ;

thf_binary_type: thf_mapping_type { $$ = strdup($1); /* store in binary_type */ }
    | thf_xprod_type  { $$ = strdup($1); /* store in binary_type */ }
    | thf_union_type  { $$ = strdup($1); /* store in binary_type */ }
    ;
thf_mapping_type: thf_unitary_type ARROW thf_unitary_type { snprintf(aux, sizeof(aux),"%s -> %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the arrow basic formula*/}
    | thf_unitary_type ARROW thf_mapping_type { snprintf(aux, sizeof(aux),"%s -> %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the arrow compose formula*/}
    ;

thf_xprod_type: thf_unitary_type STAR thf_unitary_type { snprintf(aux, sizeof(aux),"%s * %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the star basic formula*/}
    | thf_xprod_type STAR thf_unitary_type { snprintf(aux, sizeof(aux),"%s * %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the star compose formula*/}
    ;

thf_union_type: thf_unitary_type PLUS thf_unitary_type { snprintf(aux, sizeof(aux),"%s + %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the plus compose formula*/}
    | thf_union_type PLUS thf_unitary_type { snprintf(aux, sizeof(aux),"%s + %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the plus compose formula*/}
    ;

thf_sequent: thf_tuple GENTZ_ARROW thf_tuple { snprintf(aux, sizeof(aux),"%s IMPLIES(GENTZ) %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the sequent implies*/}
    | OPAREN thf_sequent CPAREN { snprintf(aux, sizeof(aux),"(%s)", $2);
                                        $$ = strdup(aux); /*we parser the parenthesis sequent */}
    ;

thf_tuple: OBRA CBRA { $$ = strdup("[]"); /*we parser the empty bracket formula */}
    | OBRA thf_formula_list CBRA { snprintf(aux, sizeof(aux),"[%s]", $2);
                                        $$ = strdup(aux); /*we parser the bracket  formula */}
    | OKEY CKEY { $$ = strdup("{}"); /*we parser the empty braces formula */}
    | OKEY thf_formula_list CKEY { snprintf(aux, sizeof(aux),"{%s}", $2);
                                        $$ = strdup(aux); /*we parser the braces formula */}
    ;

thf_formula_list: thf_logic_formula {$$ = $1; /* in this case we send directly the formula */}
    | thf_logic_formula COMMA thf_logic_formula { snprintf(aux, sizeof(aux),"%s , %s", $1, $3);
                                        $$ = strdup(aux); /*we parser the , formula */}
    ;

thf_quantifier: fof_quantifier {$$ = strdup($1); /* we send up the saved token */}
    | th0_quantifier {$$ = strdup($1); /* we send up the saved token */}
    | th1_quantifier {$$ = strdup($1); /* we send up the saved token */}
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
    | binary_connective {$$ = strdup($1); /* we send up binary_connective Char */}
    | ASSIGNMENT { $$ = strdup(":"); /* --CHECK AGAIN!! MAYBE WE NEED CHANGE IT?-- */}
    ;

thf_unary_connective: UNARY_CONNECTIVE {}
    | th1_unary_connective {$$ = strdup($1); /**/}
    ;
th1_unary_connective: FORALL_COMB { $$ = strdup("FORALL"); /* bottom of the tree we save here the token*/}
    | EXISTS_COMB { $$ = strdup("EXISTS"); /* bottom of the tree we save here the token*/}
    | CHOICE_COMB{ $$ = strdup("choice"); /* bottom of the tree we save here the token*/}
    | DESCRIPTION_COMB { $$ = strdup("THE"); /* bottom of the tree we save here the token*/}
    | EQUAL_COMB {$$ = strdup("="); /* bottom of the tree we save here the token*/ }
    ;

// LANGUAGE WORDS
atom: untyped_atom {$$ = strdup($1); /*send up the functor*/}
    | DOLLAR_WORD {$$ = strdup($1); /* bottom of the tree we save here the token*/}
    ;

untyped_atom: constant {$$ = strdup($1); /* we send up the FUNCTOR */}
    ;

constant: FUNCTOR {$$ = strdup($1); /*bottom of the tree we save here the token*/}
    ;

defined_term: NUMBER {$$ = strdup($1); /*bottom of the tree we save here the token*/}
    | DISTINCT_OBJECT {$$ = strdup($1); /*bottom of the tree we save here the token*/}
    ;

binary_connective: IFF {$$ = strdup(" = "); /*we convert the token to PVS*/}
    | IMPLIES {$$ = strdup(" => "); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NIFF {$$ = strdup("NIFF"); /* --WARNING - NOT DIRECT CONVERSION-- */}
    | NOR {$$ = strdup("NOR"); /* --WARNING - NOT DIRECT CONVERSION--  */}
    | NAND {$$ = strdup("NAND"); /* --WARNING - NOT DIRECT CONVERSION--  */}
    ;

assoc_connective: VLINE {$$ = strdup("OR"); /*bottom of the tree we save here the token*/}
    | AND {$$ = strdup("AND"); /*bottom of the tree we save here the token*/}
    ;
%%

int main(int argc, char *argv[]) {
char outputFileName[25];
FILE *outputFile;
extern FILE *yyin;

	switch (argc) {
		case 1:	yyin=stdin;
			// We create an Output File
            strncpy(outputFileName, "Output", sizeof(outputFileName) - 5);
            outputFileName[sizeof(outputFileName) - 5] = '\0';
            strcat(outputFileName, ".pvs");

            outputFile = freopen(outputFileName, "w", stdout);
            if (outputFile == NULL) {
                printf("ERROR: No se ha podido crear el archivo de salida.\n");
                fclose(yyin);
                return 1;
            }
            yyparse();
            fclose(outputFile);
			break;
		case 2: yyin = fopen(argv[1], "r");
			if (yyin == NULL) {
				printf("ERROR: No se ha podido abrir el fichero.\r\n");
			}
			else {            
				yyparse();
				fclose(yyin);
			}
			break;
		default: printf("ERROR: Demasiados argumentos.\nSintaxis: %s [fichero_entrada]\n\n", argv[0]);
	}

	return 0;
}


void yyerror (char const *message) { fprintf (stderr, "%s\r\n", message);}