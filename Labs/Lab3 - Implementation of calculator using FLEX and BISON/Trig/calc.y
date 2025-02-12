%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int yylex(void);
void yyerror(const char *s);

double result;  // Store the final result
%}

%union {
    double dval;
}

%token <dval> NUMBER
%token PLUS MINUS TIMES DIVIDE LPAREN RPAREN SIN COS ASIN ACOS PI

%type <dval> expr

%left PLUS MINUS
%left TIMES DIVIDE

%%

input:
    | input expr '\n' { 
        result = $2; 
        printf("Result: %g\n\n\n", result);
    }
    ;

expr:
      expr PLUS expr   { $$ = $1 + $3; }
    | expr MINUS expr  { $$ = $1 - $3; }
    | expr TIMES expr  { $$ = $1 * $3; }
    | expr DIVIDE expr {
        if ($3 == 0) {
            yyerror("Error: Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | LPAREN expr RPAREN { $$ = $2; }
    | SIN LPAREN expr RPAREN { $$ = sin($3); }
    | COS LPAREN expr RPAREN { $$ = cos($3); }
    | ASIN LPAREN expr RPAREN {
        if ($3 < -1 || $3 > 1) {
            yyerror("Error: asin domain error");
            $$ = 0;
        } else {
            $$ = asin($3);
        }
    }
    | ACOS LPAREN expr RPAREN {
        if ($3 < -1 || $3 > 1) {
            yyerror("Error: acos domain error");
            $$ = 0;
        } else {
            $$ = acos($3);
        }
    }
    | PI { $$ = 3.141592653589793; }
    | NUMBER { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
    printf("Enter expression (or Ctrl+C to exit):\n");

    while (1) {
        printf("> ");  
        if (yyparse() != 0) {  
            break;  
        }
    }

    return 0;
}
