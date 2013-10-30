%{
/* C code to be copied verbatim */
#include <stdio.h>
%}

%option noyywrap
%option yylineno

letter [a-zA-Z]
digit [0-9]
integ [0-9]+

%%


    /*** Rules section ***/

    /* [0-9]+ matches a string of one or more digits */
[0-9]+  {
            /* yytext is a string containing the matched text. */
            printf("Saw an integer: %s\n", yytext);
        }

.|\n    {   /* Ignore all other characters. */   }



%%

int main(void)
{
	yylex();
	return 0;
}



