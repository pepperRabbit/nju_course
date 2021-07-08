%{
	#include <stdio.h>
	#include "syntax.tab.h"
	#include "tree.h"
	int yycolumn=1;
	#define YY_USER_ACTION\
		yylloc.first_line=yylloc.last_line=yylineno;\
		yylloc.first_column=yycolumn;\
		yylloc.last_column=yycolumn+yyleng-1;\
		yycolumn+=yyleng;
	extern bool error;
%}

%option yylineno
WS [ \t]+
LINE [\n\r]+
DIGIT [0-9]
LETTER [_a-zA-Z]
ID {LETTER}({LETTER}|{DIGIT})*
INT 0|[1-9]{DIGIT}*
RELOP >|<|==|!=|>=|<=
FLOAT {DIGIT}*\.{DIGIT}+|{DIGIT}+\.
EFLOAT {FLOAT}[eE][+-]?{DIGIT}+
EFLOATERROR {FLOAT}[eE][+-]?|{FLOAT}[eE][+-]?{DIGIT}*\.{DIGIT}*
SEMI ;
COMMA ,
ASSIGNOP =
PLUS \+
MINUS \-
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}

%%
{WS} {}
{LINE} {yycolumn=1;}
{INT} {yylval.type_node=create(true,INT,"INT",yytext,yylineno); return INT;}
{FLOAT} {yylval.type_node=create(true,FLOAT,"FLOAT",yytext,yylineno); return FLOAT;}
{EFLOAT} {yylval.type_node=create(true,FLOAT,"FLOAT",yytext,yylineno); return FLOAT;}
{EFLOATERROR} {error=true; printf("Error type A at Line %d: Illegal floating point number \'%s\'\n",yylineno, yytext);}
{RELOP} {yylval.type_node=create(true,RELOP,"RELOP",yytext,yylineno); return RELOP;}
{SEMI} {yylval.type_node=create(true,SEMI,"SEMI",yytext,yylineno); return SEMI;}
{COMMA} {yylval.type_node=create(true,COMMA,"COMMA",yytext,yylineno); return COMMA;}
{ASSIGNOP} {yylval.type_node=create(true,ASSIGNOP,"ASSIGNOP",yytext,yylineno); return ASSIGNOP;}
{PLUS} {yylval.type_node=create(true,PLUS,"PLUS",yytext,yylineno); return PLUS;}
{MINUS} {yylval.type_node=create(true,MINUS,"MINUS",yytext,yylineno); return MINUS;}
{STAR} {yylval.type_node=create(true,STAR,"STAR",yytext,yylineno); return STAR;}
{DIV} {yylval.type_node=create(true,DIV,"DIV",yytext,yylineno); return DIV;}
{AND} {yylval.type_node=create(true,AND,"AND",yytext,yylineno); return AND;}
{OR} {yylval.type_node=create(true,OR,"OR",yytext,yylineno); return OR;}
{DOT} {yylval.type_node=create(true,DOT,"DOT",yytext,yylineno); return DOT;}
{NOT} {yylval.type_node=create(true,NOT,"NOT",yytext,yylineno); return NOT;}
{LP} {yylval.type_node=create(true,LP,"LP",yytext,yylineno); return LP;}
{RP} {yylval.type_node=create(true,RP,"RP",yytext,yylineno); return RP;}
{LB} {yylval.type_node=create(true,LB,"LB",yytext,yylineno); return LB;}
{RB} {yylval.type_node=create(true,RB,"RB",yytext,yylineno); return RB;}
{LC} {yylval.type_node=create(true,LC,"LC",yytext,yylineno); return LC;}
{RC} {yylval.type_node=create(true,RC,"RC",yytext,yylineno); return RC;}
"int"|"float" {yylval.type_node=create(true,TYPE,"TYPE",yytext,yylineno); return TYPE;}
"struct" {yylval.type_node=create(true,STRUCT,"STRUCT",yytext,yylineno); return STRUCT;}
"return" {yylval.type_node=create(true,RETURN,"RETURN",yytext,yylineno); return RETURN;}
"if" {yylval.type_node=create(true,IF,"IF",yytext,yylineno); return IF;}
"else" {yylval.type_node=create(true,ELSE,"ELSE",yytext,yylineno); return ELSE;}
"while" {yylval.type_node=create(true,WHILE,"WHILE",yytext,yylineno); return WHILE;}
{ID} {yylval.type_node=create(true,ID,"ID",yytext,yylineno); return ID;}
. {error=true; printf("Error type A at Line %d: Mysterious character \'%s\'\n",yylineno, yytext);}

%%
