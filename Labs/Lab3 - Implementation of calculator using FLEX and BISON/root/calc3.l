%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc3.tab.h"
%}

%%

[0-9]+(\.[0-9]+)?  { yylval.val = atof(yytext); return NUMBER; }
\+                 { return '+'; }
\-                 { return '-'; }
\*                 { return '*'; }
\(                 { return '('; }
\)                 { return ')'; }
[Ss][Qq][Rr][Tt]   { return SQRT; }
[Cc][Qq][Rr][Tt]   { return CQRT; }
\n                 { return '\n'; }
[ \t]              { /* Ignore whitespace */ }
.                  { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() { return 1; }
