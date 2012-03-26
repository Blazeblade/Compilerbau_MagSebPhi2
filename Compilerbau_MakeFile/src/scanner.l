/* 
 * scanner.l - Scanner utility for the DHBW compiler
 */

%{
	#include "parser.h"
%}

/* 
 * Default setting for flex which indicates that yytext, which is one of the main connections
 * between the scanner and parser, is handled as pointer of char instead of an array of char. 
*/
%pointer	

/* save the line number of terminals */
%option yylineno

/* finish after scanning the provided file */
%option noyywrap		

%%
\n			/* new line */
[\t ]+		/* ignore white spaces */
\/\/.*\n 	/* ignore comments */

do 	return DO;
while 	return WHILE;
if	return IF;
else 	return ELSE;
int 	return INT;
void 	return VOID;
return	return RETURN;
: 	return COLON;
, 	return COMMA;
; 	return SEMICOLON;
\{ 	return BRACE_OPEN;
\} 	return BRACE_CLOSE;
<<EOF>> return 0;

[a-zA-Z_][a-zA-Z0-9_]* 	return ID;
0|[1-9][0-9]*		return NUM;

= 		return ASSIGN;
\|\|	return LOGICAL_OR;
!		return LOGICAL_NOT;
&&		return LOGICAL_AND;
\<\<	return SHIFT_LEFT;
\>\>	return SHIFT_RIGHT;
==		return EQ;
!=		return NE;
\<		return LS;
\<=		return LSEQ;
\>=		return GTEQ;
\>		return GT;
\+		return PLUS;
\-		return MINUS;
\*		return MUL;
\-\-	return UNARY_MINUS;
\+\+	return UNARY_PLUS;
\[		return BRACKET_OPEN;
\]		return BRACKET_CLOSE;
\(		return PARA_OPEN;
\)		return PARA_CLOSE;
