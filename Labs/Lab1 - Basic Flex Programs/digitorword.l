%{
#include <stdio.h>
%}

%%
[0-9]+       { printf("Digit: %s\n", yytext); }
[a-zA-Z]+    { printf("Word: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}
