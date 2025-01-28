%{
#include <stdio.h>
%}

%%
[A-Z]       { printf("Uppercase: %s\n", yytext); }
[a-z]       { printf("Lowercase: %s\n", yytext); }
.           { printf("Other: %s\n", yytext); }
%%
int yywrap(){}
int main() {
    yylex();
    return 0;
}
