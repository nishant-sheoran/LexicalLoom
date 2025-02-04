%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    float fval;
}

%token <fval> NUMBER
%token PLUS MULT SIN COS ASIN ACOS
%token LPAREN RPAREN
%left PLUS
%left MULT
%right SIN COS ASIN ACOS

%type <fval> expr

%%

input:
    | input expr '\n' { printf("Result: %f\n", $2); }
    ;

expr:
      NUMBER          { $$ = $1; }
    | expr PLUS expr  { $$ = $1 + $3; }
    | expr MULT expr  { $$ = $1 * $3; }
    | SIN LPAREN expr RPAREN  { $$ = sin($3); }
    | COS LPAREN expr RPAREN  { $$ = cos($3); }
    | ASIN LPAREN expr RPAREN { $$ = asin($3); }
    | ACOS LPAREN expr RPAREN { $$ = acos($3); }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

%%

int main() {
    printf("Enter expressions (Ctrl+D to exit):\n");
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
