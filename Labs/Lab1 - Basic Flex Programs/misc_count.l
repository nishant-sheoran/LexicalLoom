%{
#include <stdio.h>
int line_count = 0, space_count = 0, tab_count = 0;
%}

%%
\n           { line_count++; }
\t           { tab_count++; }
[ ]          { space_count++; }
%%
int yywrap(){}
int main() {
    yylex();
    printf("Lines: %d, Spaces: %d, Tabs: %d\n", line_count, space_count, tab_count);
    return 0;
}
