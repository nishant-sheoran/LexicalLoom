%{
#include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*   { printf("Identifier: %s\n", yytext); }
%%
int yywrap(){}
int main() {
    yylex();
    return 0;
}
