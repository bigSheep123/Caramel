/*test.y*/
%{
#include <stdio.h>
#include <string.h>
int yylex(void);   // 定义的
void yyerror(char *);  // 定义的
%}

%token NUM ADD SUB MUL DIV VAR CR   // 会被翻译为C头文件


// BNF （巴克斯范式）  移进和归约 
%%
       line_list: line
                | line_list line
                ;
				
	       line : expression CR  {printf("YES\n");}

      expression: term 
                | expression ADD term
				| expression SUB term
                ;

            term: single
				| term MUL single
				| term DIV single
				;
				
		  single: NUM
				| VAR
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
    yyparse();  // bison的语法分析函数
}


定义(definations)
%%
规则(rules)
%%
代码(user code)
