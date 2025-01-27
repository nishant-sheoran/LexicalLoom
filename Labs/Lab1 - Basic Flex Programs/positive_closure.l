%{
#include <stdio.h>
%}

%%
[0-9]+       { printf("Positive number: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}
