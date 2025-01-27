%{
#include <stdio.h>
%}

%%
[+\-*/=<>]   { printf("Operator: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}
