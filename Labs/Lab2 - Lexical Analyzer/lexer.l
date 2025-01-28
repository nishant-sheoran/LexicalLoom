%{
#include <stdio.h>
#include <string.h>

int line_no = 1;
int token_no = 1;
%}

%%
\n               { line_no++; } // Increment line number on a newline

"int"|"return"   { printf("%d\t%d\tkeyword\t%s\n", token_no++, line_no, yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("%d\t%d\tidentifier\t%s\n", token_no++, line_no, yytext); }
[0-9]+           { printf("%d\t%d\tconstant\t%s\n", token_no++, line_no, yytext); }
[(){}]           { printf("%d\t%d\tbracket\t%s\n", token_no++, line_no, yytext); }
[.;]             { printf("%d\t%d\tspecial symbols\t%s\n", token_no++, line_no, yytext); }
[ \t]            ; // Ignore spaces and tabs
.                { printf("%d\t%d\tunknown\t%s\n", token_no++, line_no, yytext); }
%%
int yywrap() {
    return 1; // Indicates no more input
}

int main() {
    printf("TOKEN NO\tLINE NO\tTOKEN\t\tLEXEME\n");
    yylex();
    return 0;
}
