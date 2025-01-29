%{
#include <stdio.h>
int balance = 0;
%}

%%
\(           { balance++; }
\)           { balance--; }
%%
int yywrap(){}
int main() {
    yylex();
    if (balance == 0) printf("Well-formed parenthesis.\n");
    else printf("Not well-formed.\n");
    return 0;
}
