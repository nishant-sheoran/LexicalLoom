%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

/* Define a union to store numerical values */
%union {
    double val;
}

/* Declare token data types */
%token <val> NUMBER
%token SQRT CQRT
%token '+' '-' '*'

/* Declare expression return type */
%type <val> expr

%left '+' '-'
%left '*'

%%

input: /* empty */
     | input line
     ;

line: '\n'
    | expr '\n' { printf("Result: %lf\n", $1); fflush(stdout); }
    ;

expr: NUMBER { $$ = $1; }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | SQRT '(' expr ')' { $$ = sqrt($3); }
    | CQRT '(' expr ')' { $$ = cbrt($3); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expressions (Ctrl+D to exit):\n");
    return yyparse();
}
