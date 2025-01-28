%{
#include <stdio.h>
int line_count = 0, char_count = 0;
%}

%%
\n           { line_count++; char_count++; }
.            { char_count++; }
%%
int yywrap(){}
int main() {
    yylex();
    printf("Lines: %d, Characters: %d\n", line_count, char_count);
    return 0;
}
