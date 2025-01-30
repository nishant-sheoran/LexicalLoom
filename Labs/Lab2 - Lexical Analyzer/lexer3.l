%{
#include <stdio.h>
#include <string.h>

// Tracking count
int line_no = 1;
int token_no = 1;
int total_keywords = 0;
int total_identifiers = 0;
int total_constants = 0;
int total_brackets = 0;
int total_special = 0;

//array to store 
char keywords[100][50];
char identifiers[100][50];
char constants[100][50];
char brackets[100][50];
char special_symbols[100][50];
char unknowns[100][50];
char buffer[10000] = "";
// add to arrays
void add_to_list(char list[][50], int *count, char *token) {
    strcpy(list[*count], token);
    (*count)++;
}
%}

%option noyywrap

%%
\n                  { line_no++; }
"int"|"return"|"if"|"else" {
                        printf("%d\t%d\tkeyword\t\t%s\n", token_no++, line_no, yytext);
                        add_to_list(keywords, &total_keywords, yytext);
                     }
[a-zA-Z_][a-zA-Z0-9_]* { 
                        printf("%d\t%d\tidentifier\t%s\n", token_no++, line_no, yytext);
                        add_to_list(identifiers, &total_identifiers, yytext);
                     }
[-+]?[0-9]*\.?[0-9]*               { 
                        printf("%d\t%d\tconstant\t%s\n", token_no++, line_no, yytext);
                        add_to_list(constants, &total_constants, yytext);
                     }// eill handle float values
[(){}]               { 
                        printf("%d\t%d\tbracket\t\t%s\n", token_no++, line_no, yytext);
                        add_to_list(brackets, &total_brackets, yytext);
                     }
[.;]                 { 
                        printf("%d\t%d\tspecial symbols\t%s\n", token_no++, line_no, yytext);
                        add_to_list(special_symbols, &total_special, yytext);
                     }
[ \t]                ; // Ignore spaces and tabs
. {
    printf("%d\t%d\tunknown\t\t%s\n", token_no++, line_no, yytext);
    add_to_list(unknowns, &total_special, yytext);
}

%%

int main() {
    printf("Enter code to Check (type 'end' on a new line to process or press Ctrl+Z/Ctrl+D for EOF):-\n");
    
    while (1) {
        char line[1024];
        if (fgets(line, sizeof(line), stdin) == NULL || strcmp(line, "end\n") == 0) { 
            // EOF or "end" detected, process the buffer
            YY_BUFFER_STATE bp = yy_scan_string(buffer);
            printf("\n\nTOKEN NO\tLINE NO\tTOKEN\t\tLEXEME\n");
            yylex();
            yy_delete_buffer(bp);
            break;
        }
        strcat(buffer, line); // Append input line to the buffer
    }
    
    printf("\n\nSummary:\n");
    printf("KEYWORDS        IDENTIFIERS     CONSTANTS       BRACKETS        SPECIAL SYMBOLS\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", total_keywords, total_identifiers, total_constants, total_brackets, total_special);
    
    printf("\nClassified Tokens:\n");
    if (total_keywords > 0) {
        printf("Keywords:\n");
        for (int i = 0; i < total_keywords; i++) {
            printf("%s ", keywords[i]);
        }
        printf("\n");
    }

    if (total_identifiers > 0) {
        printf("Identifiers:\n");
        for (int i = 0; i < total_identifiers; i++) {
            printf("%s ", identifiers[i]);
        }
        printf("\n");
    }

    if (total_constants > 0) {
        printf("Constants:\n");
        for (int i = 0; i < total_constants; i++) {
            printf("%s ", constants[i]);
        }
        printf("\n");
    }

    if (total_brackets > 0) {
        printf("Brackets:\n");
        for (int i = 0; i < total_brackets; i++) {
            printf("%s ", brackets[i]);
        }
        printf("\n");
    }

    if (total_special > 0) {
        printf("Special Symbols:\n");
        for (int i = 0; i < total_special; i++) {
            printf("%s ", special_symbols[i]);
        }
        printf("\n");
    }

    if (total_special > 0) {
        printf("Unknowns:\n");
        for (int i = 0; i < total_special; i++) {
            printf("%s ", unknowns[i]);
        }
        printf("\n");
    }

    return 0;

}