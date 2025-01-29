%{
#include <stdio.h>
#include <string.h>

int line_no = 1;
int token_no = 1;
int total_keywords=0;
int total_identifiers=0;
int total_constants=0;
int total_brackets=0;
int total_special=0;
char buffer[10000]; // Buffer to hold input
%}

%%

\n               { line_no++; } // Increment line number on a newline

"int"|"return"   { printf("%d\t%d\tkeyword\t%s\n", token_no++, line_no, yytext); total_keywords++;}
[a-zA-Z_][a-zA-Z0-9_]* { printf("%d\t%d\tidentifier\t%s\n", token_no++, line_no, yytext); total_identifiers++;}
[0-9]+           { printf("%d\t%d\tconstant\t%s\n", token_no++, line_no, yytext); total_constants++;}
[(){}]           { printf("%d\t%d\tbracket\t%s\n", token_no++, line_no, yytext); total_brackets++;}
[.;]             { printf("%d\t%d\tspecial symbols\t%s\n", token_no++, line_no, yytext); total_special++;}
[ \t]            ; // Ignore spaces and tabs
.                { printf("%d\t%d\tunknown\t%s\n", token_no++, line_no, yytext); }
%%

int yywrap() {
    return 1; // Indicates no more input
}

int main() {
    printf("Enter code to Check (type 'end' on a new line to process):-\n");
   
    while (1) {
        char line[1024];
        fgets(line, sizeof(line), stdin); // Read a line of input

        if (strcmp(line, "end\n") == 0) {
            // End detected, process the buffer
            YY_BUFFER_STATE bp = yy_scan_string(buffer);
            printf("TOKEN NO\tLINE NO\tTOKEN\t\tLEXEME\n");
            yylex();
            yy_delete_buffer(bp);
            break;
        } else {
            strcat(buffer, line); // Append input line to the buffer
        }
    }
    printf("\n\nTotal no of:-\nKEYWORDS\tIDENTIFIERS\tCONSTANTS\tBRACKETS\tSPECIAL CHARACTERS\n");
    printf("%d\t%d\t%d\t%d\t%d\n",total_keywords,total_identifiers,total_constants,total_brackets,total_special);
    return 0;
}
