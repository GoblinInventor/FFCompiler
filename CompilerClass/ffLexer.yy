%option noyywrap
%option yylineno

letter [a-zA-Z]
digit [0-9]
integ [0-9]+

%%

PROC										{return(6);}
ENDPROC									{return(7);}
IS										{return(8);}
DECL										{return(9);}
CONST										{return(10);}
(RAT|REL|INT)					{return(11);}
IF											{return(12);}
EIF										{return(13);}
ELSE											{return(14);}
THEN											{return(15);}
WHEN										{return(16);}
WHILE											{return(17);}
PR_OUT										{return(18);}
RE_IN										{return(19);}
BEG											{return(20);}
END											{return(21);}
ASSERT										{return(22);}
NOT											{return(23);}
"<"|"="|">"											{return(24);}
";"									{return(25);}
"+"|"or"|"-"						{return(32);}
"*"|"and"|"/"						{return(33);}
":"											{return(26);}
DEF										{return(27);}
"("											{return(28);}
")"												{return(29);}
LOOP											{return(31);}
{letter}({letter}|{digit})*			{return(1);}
{digit}+"."{digit}*								{return(2);}
{digit}+											{return(3);}
(true|false)									{return(4);}
"\"{letter}*\""						{return(5);}
[ \n\t]								{return(32);}
%%

#include <stdio.h>
#include <iostream>
int main(int argc, char* argv[])
{
	int  p;
//Read until out of file
	while (p=yylex()) {
//print the pth lex (printing #(p) is lex result
	printf("%d is \%s\n", p, yytext);
    }
	return(0);
}



