%{
#include <stdio.h>
int char_count = 0;
%}

%%
.            { char_count++; }
%%

int main() {
    yylex();
    printf("Total Characters: %d\n", char_count);
    return 0;
}
