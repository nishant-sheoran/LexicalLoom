%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    double num;
}

%token <num> NUMBER
%type <num> expression equation  /* <<< Added this line */

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

equation:
      expression '\n'  { printf("= %lf\n", $1); }
    | equation expression '\n' { printf("= %lf\n", $2); }
    ;

expression:
      NUMBER          { $$ = $1; }
    | expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { 
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
      }
    | '(' expression ')' { $$ = $2; }
    | '-' expression %prec UMINUS { $$ = -$2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expressions to evaluate:\n");
    yyparse();
    return 0;
}
