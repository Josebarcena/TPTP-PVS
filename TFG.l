%{

#include "structs.h"
#include "TFG.tab.h"

static int firstToken = 1; // Bandera para detectar el primer token

void reset_firstToken() {
    firstToken = 1;
}

%}
%option yylineno

axiom "axiom"
hypothesis "hypothesis"
definition "definition"
lemma "lemma"
theorem "theorem"
conjecture "conjecture"
negatedConjecture "negated_conjecture"
type "type"
assumption "assumption"
plain "plain"
unknown "unknown" 

typedHighLogic "thf"
typedFirstLogic "tff"
firstLogic "fof"
normalForm "cnf"
negationNormalForm "nhf"
negationExtendedForm "nxf"
normalizedTypedForm "ntf"
letterMinus [a-z]
letterMayus [A-Z]
numeric -?[0-9]
symbolsVar [_]
Alpha_numeric ([a-zA-Z0-9_])

vLine "|"

equalComb "@="
descriptcionComb "@@-"
existsComb "??"
choiceComb "@@+"
forAllComb "!!"
gentzArrow "-->"


thfPlus "@+"
thfMinus "@-"
infixInequality "!="
iff "<=>"
implies "=>"
if "<="
nIff "<~>"
nOr "~|"
nAnd "~&"
not "~"
tyForAll "!>"
choice "@+"
description "@-"
subtype_sign "<<"
assignment ":="

and "&"
application "@"
equal "="
greater ">"
less "<"
mult "*"
minus "-"
plus "+"
forAll "!"
exists "?"
hash "#"
lambda "^"
dollar "$"
div "%".*
multiBlock [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]

includeFile '([A-Za-z0-9.-]("/"[A-Za-z0-9.-])?)+'
upperWord -?{letterMayus}({Alpha_numeric}*)
lowerWord {letterMinus}({Alpha_numeric}*)
dollarWord {dollar}({Alpha_numeric}+)
dollarDollarWord {dollar}{dollar}({Alpha_numeric}+)
var {upperWord}
functor {lowerWord}
distinctObject """ [A-z] """
systemConstant {dollarDollarWord}

include "include"
let {dollar}"let"
let1 {dollar}"letft"
let2 {dollar}"lettt"

oParen "("
cParen ")"
oBra "["
cBra "]"
oKey "\{"
cKey "\}"
comma ","
dot "."
doubleDot ":"


ignore .|[-\s\n\t]

%%
{typedHighLogic} { firstToken = 0; return THF;}
{typedFirstLogic} {firstToken = 0; return TFF;}

{axiom} { return AXIOM;}
{hypothesis} { return HYPOTHESIS;}
{definition} { return DEFINITION;}
{lemma} { return LEMMA;}
{theorem} { return THEOREM;}
{conjecture} { return CONJECTURE;}
{negatedConjecture} { return NEGATEDCONJ;}
{type} { return TYPE;}
{assumption} { return ASSUMPTION;}
{plain} { return PLAIN;}
{unknown} { return UNKNOWN;}

{include} {return INCLUDE_HEADER;}
{let} {return LET;}
{let1} {return LET1;}
{let2} {return LET2;}

{div} {if(firstToken){ 
        yylval.valChar = strdup(yytext); 
        return DIV;}}
{multiBlock} {if(firstToken){
        yylval.valChar = strdup(yytext);
        return MULTIBLOCK;}}


{includeFile} {yylval.valChar = strdup(yytext); return INCLUDE_FILE;}
{var} { yylval.valChar = strdup(yytext); return VAR;}
{functor} {yylval.valChar = strdup(yytext);  return FUNCTOR;}
{dollarWord} {yylval.valChar = strdup(yytext); return DOLLAR_WORD;}
{systemConstant} {yylval.valChar = strdup(yytext); return SYSTEM_CONSTANT;}
{distinctObject} {yylval.valChar = strdup(yytext);  return DISTINCT_OBJECT;}
{numeric}+ {yylval.valChar = strdup(yytext); return NUMBER;}

{infixInequality} {return INFIX_INEQUALITY;}
{iff} {return IFF;}
{implies} {return IMPLIES;}
{nIff} {return NIFF;}
{nOr} {return NOR;}
{nAnd} {return NAND;}
{exists} {return EXISTS;}
{tyForAll} {return TYPED_FORALL;}
{choice} {return CHOICE;}
{description} {return DESCRIPTION;}
{subtype_sign} {return SUBTYPE_SIGN;}
{assignment} {return ASSIGNMENT;}

{equal} {return INFIX_EQUALITY;}
{and} {return AND;}
{application} {return APPLICATION;}
{greater} {return ARROW;}
{mult} { return STAR;}
{plus} {return PLUS;}
{forAll} {return FORALL;}
{lambda} {return LAMBDA;}

{vLine} { return VLINE;}

{oParen} {return OPAREN;}
{cParen} {return CPAREN;}
{oBra} {return OBRA;}
{cBra} {return CBRA;}
{oKey} {return OKEY;}
{cKey} {return CKEY;}
{comma} {return COMMA;}
{dot} {return DOT;}
{doubleDot} {return DDOT;}

{ignore} 
%%
