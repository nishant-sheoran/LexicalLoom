%{
#include <stdio.h>
%}

%%
[+\-*/=<>]   { printf("Operator: %s\n", yytext); }
%%
int yywrap(){}
int main() {
    yylex();
    return 0;
}
