%{
#include <stdio.h>
int word_count = 0;
%}

%%
target_word   { word_count++; }
%%
int yywrap(){}
int main() {
    printf("Enter the word to search: ");
    scanf("%s", target_word);
    yylex();
    printf("Frequency of '%s': %d\n", target_word, word_count);
    return 0;
}
