%{
/* SO 5008-7213 */
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern int len;
%}

%option noyywrap
%option noinput
%option nounput
letter [a-zA-Z]+

%%
(\-)?{letter}       {printf("L1: [%s]\n", yytext); yylval.id=yytext;len=yyleng;return WORD;}
[ \t\n]             {printf("L2: [%s]\n", yytext);}
.                   {printf("L3: [%s]\n", yytext); return NOTOKEN;}
%%

