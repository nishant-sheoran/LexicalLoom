%{
#include <stdio.h>
int pos_count = 0, neg_count = 0;
%}

%%
[0-9]+       { pos_count++; printf("Positive: %s\n", yytext); }
-[0-9]+      { neg_count++; printf("Negative: %s\n", yytext); }
%%

int main() {
    yylex();
    printf("Positive Numbers: %d, Negative Numbers: %d\n", pos_count, neg_count);
    return 0;
}
