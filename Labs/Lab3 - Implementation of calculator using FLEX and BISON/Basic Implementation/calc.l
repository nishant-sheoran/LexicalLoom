%{
#include "y.tab.h"
%}

%%
[0-9]+        { yylval.num = atoi(yytext); return NUMBER; }
[+\-*/()]     { return yytext[0]; }
[ \t\n]       ;  /* Ignore spaces and newlines */
.              { return yytext[0]; }
%%

int yywrap() { return 1; }