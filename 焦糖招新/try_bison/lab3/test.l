%{
#define YYSTYPE double
#include <stdio.h>
#include "y.tab.h"
void yyerror(char *);
%}
NUM      -?([0-9]+|[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)
%%

{NUM}		                {yylval = atof(yytext); return NUM;}
"+"							return ADD;
"-"							return SUB;
"*"							return MUL;
"/"							return DIV;
\n                          return CR;
"("                         return Y_LPAR;
")"                         return Y_RPAR;
[ \t]+                    
.
%%
