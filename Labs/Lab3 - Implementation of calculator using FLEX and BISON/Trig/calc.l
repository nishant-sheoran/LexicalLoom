%{
#include <stdio.h>
#include <stdlib.h>
#include "calc.tab.h"  // Include the Bison header file

extern YYSTYPE yylval;  
%}

%%

[0-9]+(\.[0-9]+)?  { yylval.dval = atof(yytext); return NUMBER; }
"+"                { return PLUS; }
"-"                { return MINUS; }
"*"                { return TIMES; }
"/"                { return DIVIDE; }
"("                { return LPAREN; }
")"                { return RPAREN; }
"sin"              { return SIN; }
"cos"              { return COS; }
"asin"             { return ASIN; }
"acos"             { return ACOS; }
"pi"               { return PI; }
[ \t]              { /* Ignore whitespace */ }
\n                 { return '\n'; } 
.                  { printf("Invalid character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;  // End of input
}