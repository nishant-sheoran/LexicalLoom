%{
#include "calc1.tab.h"
#include <math.h>
%}

%option noyywrap

%%

[0-9]+(\.[0-9]+)?   { yylval.fval = atof(yytext); return NUMBER; }
"+"                 { return PLUS; }
"*"                 { return MULT; }
"sin"               { return SIN; }
"cos"               { return COS; }
"asin"              { return ASIN; }
"acos"              { return ACOS; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
[\t\n ]             { /* Ignore whitespace */ }
.                   { return yytext[0]; }

%%

int yywrap() { return 1; }
