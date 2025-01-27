%{
#include <stdio.h>
int token_count = 0;
%}

%%
.            { token_count++; }
%%

int main() {
    yylex();
    printf("Total Tokens: %d\n", token_count);
    return 0;
}
