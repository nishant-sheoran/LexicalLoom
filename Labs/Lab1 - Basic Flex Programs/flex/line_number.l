%{
#include <stdio.h>
int line_num = 1;
%}

%%
.*\n         { printf("%d: %s", line_num++, yytext); }
.            { printf("%d: %s", line_num++, yytext); }
%%
int yywrap(){}
int main() {
    yylex();
    return 0;
}
