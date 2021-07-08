%{
	#include <stdio.h>
	#include "lex.yy.c"
	#include "tree.h"
	extern bool error;
	extern node* root;
	#define YYERROR_VERBOSE
%}

%union {
	int type_int;
	float type_float;
	double type_double;
	struct node* type_node;
}

/* token */
%token <type_node> INT
%token <type_node> FLOAT
%token <type_node> ID
%token <type_node> SEMI COMMA
%token <type_node> ASSIGNOP RELOP
%token <type_node> PLUS MINUS STAR DIV
%token <type_node> AND OR
%token <type_node> NOT
%token <type_node> DOT
%token <type_node> LP RP LB RB LC RC
%token <type_node> IF ELSE
%token <type_node> STRUCT
%token <type_node> WHILE
%token <type_node> RETURN
%token <type_node> TYPE

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%right DOT LP RP LB RB

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%type <type_node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag
%type <type_node> VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%%
/* high level definitions*/
Program: ExtDefList{
		$$=create(false,0,"Program","",@$.first_line);
		node* childs[]={$1};
		addChild(1,$$,childs);
		root=$$;
	};

ExtDefList: /* empty */ {//$$=NULL;
		$$=create(false,0,"ExtDefList","",@$.first_line);
	}
	| ExtDef ExtDefList{
		$$=create(false,0,"ExtDefList","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	};

ExtDef: Specifier ExtDecList SEMI {
		$$=create(false,0,"ExtDef","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| Specifier SEMI /*struct*/{
		$$=create(false,0,"ExtDef","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	}
	| Specifier FunDec CompSt{
		$$=create(false,0,"ExtDef","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| error SEMI;

ExtDecList: VarDec{
		$$=create(false,0,"ExtDecList","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	}
	| VarDec COMMA ExtDecList{
		$$=create(false,0,"ExtDecList","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	};


/* specifiers */
Specifier: TYPE{
		$$=create(false,0,"Specifier","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	}
	| StructSpecifier{
		$$=create(false,0,"Specifier","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	};

StructSpecifier:STRUCT OptTag LC DefList RC{
		$$=create(false,0,"StructSpecifier","",@$.first_line);
		node* childs[]={$1,$2,$3,$4,$5};
                addChild(5,$$,childs);
	}
	| STRUCT Tag{
		$$=create(false,0,"StructSpecifier","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	}
	| STRUCT OptTag LC error RC;

OptTag: /* empty */ {//$$=NULL;
		$$=create(false,0,"OptTag","",@$.first_line);
	}
	| ID {
		$$=create(false,0,"OptTag","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	};

Tag: ID {
		$$=create(false,0,"Tag","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	};

/* declarators*/
VarDec: ID{
		$$=create(false,0,"VarDec","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	}
	| VarDec LB INT RB{
		$$=create(false,0,"VarDec","",@$.first_line);
		node* childs[]={$1,$2,$3,$4};
                addChild(4,$$,childs);
	}
	| VarDec LB error RB;

FunDec: ID LP VarList RP{
		$$=create(false,0,"FunDec","",@$.first_line);
		node* childs[]={$1,$2,$3,$4};
                addChild(4,$$,childs);
	}
	| ID LP RP{
		$$=create(false,0,"FunDec","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| ID LP error RP;

VarList: ParamDec COMMA VarList{
		$$=create(false,0,"VarList","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	|ParamDec{
		$$=create(false,0,"VarList","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	};

ParamDec: Specifier VarDec{
		$$=create(false,0,"ParamDec","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	};

/* statements*/
CompSt: LC DefList StmtList RC /* {...} */{
		$$=create(false,0,"CompSt","",@$.first_line);
		node* childs[]={$1,$2,$3,$4};
                addChild(4,$$,childs);
	}
	| LC error RC;

StmtList: /* empty */ {//$$=NULL;
		$$=create(false,0,"StmtList","",@$.first_line);
	}
	| Stmt StmtList{
		$$=create(false,0,"StmtList","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	};

Stmt: Exp SEMI{
		$$=create(false,0,"Stmt","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	}
	| CompSt {
		$$=create(false,0,"Stmt","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	}
	| RETURN Exp SEMI {
		$$=create(false,0,"Stmt","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| IF LP Exp RP Stmt {
                $$=create(false,0,"Stmt","",@$.first_line);
		node* childs[]={$1,$2,$3,$4,$5};
                addChild(5,$$,childs);
        }
	| IF LP Exp RP Stmt ELSE Stmt {
		$$=create(false,0,"Stmt","",@$.first_line);
		node* childs[]={$1,$2,$3,$4,$5,$6,$7};
                addChild(7,$$,childs);

	}
	| WHILE LP Exp RP Stmt {
		$$=create(false,0,"Stmt","",@$.first_line);
		node* childs[]={$1,$2,$3,$4,$5};
                addChild(5,$$,childs);
	}
	| error SEMI
	| RETURN error SEMI
	| IF LP error RP
	| WHILE LP error RP;

/* local definitions*/
DefList: /* empty */ {//$$=NULL;
		$$=create(false,0,"DefList","",@$.first_line);
	}
	| Def DefList {
		$$=create(false,0,"DefList","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
	};

Def: Specifier DecList SEMI {
		$$=create(false,0,"Def","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| Specifier error SEMI;

DecList: Dec {
		$$=create(false,0,"DecList","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	}
	| Dec COMMA DecList {
		$$=create(false,0,"DecList","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	};

Dec: VarDec {
                $$=create(false,0,"Dec","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
        }
	| VarDec ASSIGNOP Exp{
                $$=create(false,0,"Dec","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	};

/* expressions */
Exp: Exp ASSIGNOP Exp {
		$$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| Exp AND Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp OR Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp RELOP Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp PLUS Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp MINUS Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp STAR Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp DIV Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| LP Exp RP {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| MINUS Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
        }
	| NOT Exp {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2};
                addChild(2,$$,childs);
        }
	| ID LP Args RP {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3,$4};
                addChild(4,$$,childs);
        }
	| ID LP RP {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| Exp LB Exp RB {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3,$4};
                addChild(4,$$,childs);
        }
	| Exp DOT ID {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
        }
	| ID {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
        }
	| INT {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
        }
	| FLOAT {
                $$=create(false,0,"Exp","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
        }
	| LP error RP
	| ID LP error RP
	| Exp LB error RB;

Args: Exp COMMA Args {
		$$=create(false,0,"Args","",@$.first_line);
		node* childs[]={$1,$2,$3};
                addChild(3,$$,childs);
	}
	| Exp {
		$$=create(false,0,"Args","",@$.first_line);
		node* childs[]={$1};
                addChild(1,$$,childs);
	};


%%
void yyerror(char *msg){
	error = true;
	printf("Error Type B at Line %d: %s\n",yylineno, msg);
}
