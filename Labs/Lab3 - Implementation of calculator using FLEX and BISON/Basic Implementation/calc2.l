%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%option noyywrap

DIGIT    [0-9]
NUMBER   [-+]?{DIGIT}+\.?{DIGIT}*

%%

[ \t\n]    ;  // Ignore whitespace

{NUMBER}  {
    yylval.fval = atof(yytext); // Store the value as float
    return NUMBER;
}

[+\-*/()]  { return yytext[0]; }

.   { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap() { return 1; }
