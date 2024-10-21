/*test.l*/
%{
#include <stdio.h>
#include "y.tab.h"  // 必须需要填写 bison 在翻译代码时自动生成的头文件
void yyerror(char *);  // 既在bison中定义，也在flex中定义  bison会自动定义这个函数
//  但是我们想要使用自己编写的报错函数的话，则要重新声明它，否则会报错。
%}
NUM [1-9]+[0-9]*|0
%%
                            // 右边return 的符号是定义在y.tab.h 头文件中
                            // 实质上是来自于我们在 .y 文件中所声明的
{NUM}		                return NUM;
"+"							return ADD;
"-"							return SUB;
"*"							return MUL;
"/"							return DIV;
[a-zA-Z_$]+[a-zA-Z_$0-9]*	return VAR;
\n                          return CR;
[ \t]+                     /* ignore whitespace */;
.
%%

// flex 的第三部分直接搬到了bison的第三部分去了。
