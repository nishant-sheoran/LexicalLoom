%{
#include <stdio.h>
%}

%%
[aeiouAEIOU]   { printf("Vowel: %s\n", yytext); }
.              { printf("Not a vowel: %s\n", yytext); }
%%
int yywrap(){}
int main() {
    yylex();
    return 0;
}
