%{
#define YYSTYPE double
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int yylex(void);  //?????????????????????????????????  token
void yyerror(char *);
%}


%token ADD SUB MUL DIV CR Y_LPAR Y_RPAR
%token NUM

%%
    prog: 
        | prog expr CR { printf("= %lf\n", $2); };
    expr:
        expr ADD term { $$ = $1 + $3; }
        | expr SUB term { $$ = $1 - $3; }
        | expr ADD ADD term {$$ = $1+$4+1;}
        | term
    term:
        term MUL MUL factor { $$ = pow($1, $4); }
        | term MUL factor { $$ = $1 * $3; }
        | term DIV factor { $$ = $1 / $3; }        
        | factor
        ;
    factor:
        NUM 
        | SUB factor { $$ = -$2; }        
        | Y_LPAR expr Y_RPAR { $$ = $2; }
        ;
%%
void yyerror(char *str){
    fprintf(stderr,"error:%s\n",str);
}

int yywrap(){
    return 1;
}

int main()
{
    printf("由于负数和减法的不可区分，请按一下规范输入减式  ： 10 - 8 \n");
    printf("-----------------------------------------------------\n");
    while (1) {
        yyparse();
    }
    return 0;
}
