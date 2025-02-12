%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc2.tab.h"
%}

%%

[0-9]+(\.[0-9]+)?  { yylval.val = atof(yytext); return NUMBER; }
\-                 { return '-'; }
\/                 { return '/'; }
\(                 { return '('; }
\)                 { return ')'; }
[Ll][Oo][Gg]       { return LOG; }
[Ll][Oo][Gg]10     { return LOG10; }
\n                 { return '\n'; }
[ \t]              { /* Ignore whitespace */ }
.                  { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() { return 1; }
