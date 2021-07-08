#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

extern HashNode table[HASHNUM];
extern LayerList layerlist;
extern bool error;

int layer = 0;
int no_name_id = 1;

unsigned int hash_pjw(char* name)
{
	unsigned int val = 0, i;
	for (; *name; ++name){
		val = (val << 2) + *name;
		if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;	
	}
	return val;
}

void init()
{
	for(int i=0; i<HASHNUM; i++){
		table[i] = NULL;
	}
	// int read();
	Type t1 = (Type)malloc(sizeof(struct Type_));
	t1->kind = FUNCTION;
	t1->u.func = (Function)malloc(sizeof(struct Function_));
	t1->u.func->ret_type = (Type)malloc(sizeof(struct Type_));
	t1->u.func->ret_type->kind = BASIC;
	t1->u.func->ret_type->u.basic = INT;
	t1->u.func->param = NULL;
	insert("read", t1);
	// int write(int val);
	Type t2 = (Type)malloc(sizeof(struct Type_));
	t2->kind = FUNCTION;
	t2->u.func = (Function)malloc(sizeof(struct Function_));
	t2->u.func->ret_type = (Type)malloc(sizeof(struct Type_));
	t2->u.func->ret_type->kind = BASIC;
	t2->u.func->ret_type->u.basic = INT;
	t2->u.func->param = (FieldList)malloc(sizeof(struct FieldList_));
	t2->u.func->param->name = (char*)malloc(sizeof(char)*4);
	strcpy(t2->u.func->param->name, "val");
	t2->u.func->param->type = (Type)malloc(sizeof(struct Type_));
	t2->u.func->param->type->kind = BASIC;
	t2->u.func->param->type->u.basic = INT;
	t2->u.func->param->next = NULL;
	insert("write", t2);
}

void analyze(node* root)
{
	init();
	if(root){
		//printf("program..\n");
		ExtDefList(root->child);
	}
}

void ExtDefList(node* n)
{
	if(n->child){
		//printf("extdeflist\n");
		ExtDef(n->child);
		ExtDefList(n->child->sibling);
	}
}

void pop_layer()
{
	//if(!layerlist) printf("layerlist null!!!!!\n");
	//printf("layer:%d, layerlisthead's layer:%d\n",layer,layerlist->layer);
	LayerList delete_layer = layerlist;
	layerlist = layerlist->next;
	LayerListNode p = delete_layer->node;
	while(p){
		//printf("pop %s\n", p->hashnode->name);
		unsigned int pos = hash_pjw(p->hashnode->name);
		HashNode q = table[pos];
		HashNode t = NULL;	//node before q
		while(q!=p->hashnode){
			t = q;
			q = q->next;
		}
		//remove from hashtable
		if(t==NULL){//q is head
			table[pos] = q->next;
		}
		else{
			t->next = q->next;
		}
		p = p->next;
	}
}

void ExtDef(node* n)
{
	//printf("extdef\n");
	Type t = Specifier(n->child);
	//printf("name:%s\n",n->child->sibling->name);
	int res = strcmp(n->child->sibling->name, "FunDec");
	if(res<0){// gobal var: ExtDef->Specifier ExtDecList SEMI
		//printf("1\n");
		ExtDecList(n->child->sibling, t);
	}
	else if(res>0){// struct: ExtDef->Specifier SEMI
		//printf("2\n");
	}
	else{// func: ExtDef->Specifier FunDec CompSt
		//printf("3\n");
		HashNode h = find(n->child->sibling->child->val);
		if(h){
			error = true;
			printf("Error Type 4 at Line %d: Redefined function \"%s\"\n", n->child->sibling->child->line, n->child->sibling->child->val);
		}
		else{
			layer++;	//先加一层方便删形参节点
			LayerList l = (LayerList)malloc(sizeof(struct LayerList_));
			l->layer = layer;
			if(!layerlist) layerlist = l;
			else{
				l->next = layerlist;
				layerlist = l;
			}
			Type ntype = (Type)malloc(sizeof(struct Type_));
			ntype->kind = FUNCTION;
			ntype->u.func = FunDec(n->child->sibling);
			ntype->u.func->ret_type = t;
			insert(ntype->u.func->name, ntype);
			CompSt(n->child->sibling->sibling, ntype->u.func);
			pop_layer();
			layer--;
			/*layer++;
			LayerList l = (LayerList)malloc(sizeof(struct LayerList_));
			l->layer = layer;
			pop_layer();
			layer--;*/
		}
	}
	/*else{
		printf("error!!!\n");
	}*/
}

void ExtDecList(node* n, Type t)
{
	//printf("extdeclist\n");
	VarDec(n->child, t, false);	// ExrDecList->VarDec
	if(n->child->sibling){// ExtDecList->VarDec COMMA ExtDecList
		ExtDecList(n->child->sibling->sibling, t);
	}
}

Type Specifier(node* n)
{
	//printf("specifier:%s %s\n",n->child->name, n->child->val);
	int res = strcmp(n->child->name, "TYPE");
	if(res==0){// int/float
		//printf("1\n");
		//printf("%s\n",n->child->val);
		Type t = (Type)malloc(sizeof(struct Type_));
		t->kind = BASIC;
		if(strcmp(n->child->val,"int")==0){
			t->u.basic=INT;
			//printf("test int\n");
		}
		else t->u.basic=FLOAT;
	//printf("specifier end\n");
		return t;
	}
	else return StructSpecifier(n->child);
}

Type StructSpecifier(node* n)
{
	//printf("struct specifier\n");
	node* t = n->child->sibling;
	if(strcmp(t->name, "Tag")==0){ // use struct, check
		//printf("use\n");
		HashNode t1 = find(t->child->val);
		if(t1 && t1->type->kind==STRUCTURE){ //true
			return t1->type;
		}
		else {
			error = true;
			printf("Error Type 17 at Line %d: Undefined Structure \"%s\"\n", t->child->line, t->child->val);
		}
		return NULL;
	}
	else{ // def struct
		//printf("def\n");
		node* deflist;
		bool flag = false;
		//if(strcmp("OptTag", n->child->sibling->name)==0){ // has a name
		if(n->child->sibling->child){	// OptTag -> ID, not empty, has a name
			flag = true;
			/*先查的话struct里套一个重名的struct检查不出来，查的时候都没定义，不报错...
			HashNode t1 = find(n->child->sibling->child->val);	
			if(t1){
				printf("Error Type 16 at Line %d: Duplicated name \"%s\"\n", n->child->sibling->line,  n->child->sibling->child->val);
				return NULL;
			}*/
			deflist = n->child->sibling->sibling->sibling;
			//printf("%s\n",deflist->name);
		}
		else deflist = n->child->sibling->sibling;
		Type type = (Type)malloc(sizeof(struct Type_));
		type->kind=STRUCTURE;
		type->u.structure = DefList(deflist, true);
		//type->u.structure->name = (char*)malloc(sizeof(char)*strlen(n->child->sibling->child->val)+1);
		//strcpy(type->u.structure->name, n->child->sibling->child->val);
		if(!check_redefined(type)) return NULL;
		if(flag){ // has a name, then insert
		HashNode t1 = find(n->child->sibling->child->val);	
			if(t1){
				error = true;
				printf("Error Type 16 at Line %d: Duplicated name \"%s\"\n", n->child->sibling->line,  n->child->sibling->child->val);
				return NULL;
			}
			else insert(n->child->sibling->child->val, type);
		}
		else{
			type->u.structure->id = no_name_id;
			insert("",type);
			no_name_id++;
		}
		return type;
	}
}

void insert(char* s, Type t)
{
	//printf("insert\n");
	unsigned int pos = hash_pjw(s);
	HashNode h = (HashNode)malloc(sizeof(struct HashNode_));
	h->type = t;
	h->name = (char*)malloc(sizeof(char)*strlen(s)+1);
	if(t->kind==FUNCTION) h->layer = 0;
	else h->layer = layer;
	strcpy(h->name, s);
	if(table[pos]){
		h->next = table[pos];
	}
	table[pos] = h;
	//printf("insert half\n");
	if(layer>0 && t->kind!=FUNCTION){//{...}
		//printf("layer %d\n", layer);
		//if(!layerlist) printf("error layerlist null!!!\n");
		LayerListNode lnode = (LayerListNode)malloc(sizeof(struct LayerListNode_));
		lnode->hashnode = h;
		lnode->next = layerlist->node;
		layerlist->node = lnode;
	}
	//printf("insert end, %d:%s layer:%d\n",pos,table[pos]->name, layer);
}

FieldList VarDec(node* n, Type t, bool is_struct)
{
	if(!t) return NULL;
	//printf("vardec %s, is struct %d\n", n->child->val, is_struct);
        if(n->child->sibling){//VarDec->ID LP INT RB
		//if(is_struct){ same...
			Type t1 = (Type)malloc(sizeof(struct Type_));
			t1->kind = ARRAY;
			t1->u.array.elem = t;
			t1->u.array.size = atoi(n->child->sibling->sibling->val);
			return VarDec(n->child, t1, is_struct);
		//}
        }
        else{//VarDec->ID
			//printf("here\n");
            if(is_struct){
                FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
                f->type = t;
				//printf("3\n");
				f->name = (char*)malloc(sizeof(char)*strlen(n->child->val)+1);
				//printf("4\n");
                strcpy(f->name, n->child->val);
                f->line = n->child->line;       // check redefined field
                return f;
            }	
			else{
				//printf("here\n");
				//if(!t) printf("t null\n");
				HashNode h = find(n->child->val);
				//if(!h) printf("h null\n");
				if(h){
					if(h->type->kind==FUNCTION || h->type->kind==STRUCTURE || h->layer == layer){
						error = true;
						printf("Error Type 3 at line %d: Redefined variable \"%s\"\n", n->child->line, n->child->val);
						return NULL;
					}
				}
				//printf("here2\n");
				FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
				f->type = t;
				f->name = (char*)malloc(sizeof(char)*strlen(n->child->val)+1);
				//printf("here3\n");
				strcpy(f->name, n->child->val);
				//printf("here\n");
				insert(n->child->val, t);
				//printf("here4\n");
				//printf("end vardec\n");
				return f;
			}
        }
	return NULL;
}

Function FunDec(node* n)
{
	//printf("fundec\n");
	Function f = (Function)malloc(sizeof(struct Function_));
	f->name = (char*)malloc(sizeof(char)*strlen(n->child->val)+1);
	strcpy(f->name, n->child->val);
	if(strcmp(n->child->sibling->sibling->name,"VarList")==0){// FunDec->ID LP VarList RP
		f->param = VarList(n->child->sibling->sibling);
	}
	else{// FunDec->ID LP RP
		;
	}
	//printf("func dec end\n");
	return f;
}

FieldList VarList(node* n)
{//VarList->ParamDec
	//printf("varlist\n");
	FieldList f = ParamDec(n->child);
	if(n->child->sibling){//VarList->ParamDec COMMA VarList
		//printf("%s\n",n->child->sibling->sibling->name);
		f->next = VarList(n->child->sibling->sibling);
	}
	return f;
}

FieldList ParamDec(node* n)
{//ParamDec->Specifier VarDec
	//printf("paramdec\n");
	Type t = Specifier(n->child);
	return VarDec(n->child->sibling, t, false);
}

bool check_redefined(Type t)
{
	//printf("check redefined\n");
	FieldList p = t->u.structure;
	FieldList f = NULL;
	if(p && p->next) f = p->next;
	while(f){
		while(p!=f){
			if(strcmp(p->name, f->name)==0){
				error = true;
				printf("Error Type 15 at Line %d: Redefined field \"%s\"\n", f->line, f->name);
				return false;
			}
			p = p->next;
		}
		p = t->u.structure;
		f = f->next;
	}
	//printf("check r end\n");
	return true;
}

void CompSt(node* n, Function f)
{// CompSt->LC DefList StmtList RC
	/*printf("compst->");
	node * p = n->child;
		while(p){
			printf("%s:%s ",p->name,p->val);
			p=p->sibling;
		}
		printf("\n");*/
	/*layer++;	要检测形参和第一个{}里局部变量的冲突，遇到Stmt->CompSt再layer+1！！！
	LayerList l = (LayerList)malloc(sizeof(struct LayerList_));
	l->layer = layer;
	if(!layerlist) layerlist = l;
	else{
		l->next = layerlist;
		layerlist = l;
	}
	pop_layer();
	layer--;*/
	//printf("compst\n");
	if(strcmp(n->child->sibling->name, "DefList")==0){
		DefList(n->child->sibling, false);
		if(strcmp(n->child->sibling->sibling->name,"StmtList")==0){
			StmtList(n->child->sibling->sibling, f);
		}
	}
	else if(strcmp(n->child->sibling->name, "StmtList")==0){//deflist is null
		StmtList(n->child->sibling, f);
	}
}

void StmtList(node* n, Function f)
{//StmtList->Stmt StmtList | null
	/*printf("stmtlist->");
	node * p = n->child;
		while(p){
			printf("%s:%s ",p->name,p->val);
			p=p->sibling;
		}
		printf("\n");*/
	//printf("stmtlist\n");
	if(n->child){
		if(strcmp(n->name, "StmtList")!=0) return;	
		//if stmtlist is null, then this node is }
		Stmt(n->child, f);
		StmtList(n->child->sibling, f);
	}
	//else printf("stmtlist null\n");
	//printf("stmtlist end\n");
}

void Stmt(node* n, Function f)
{
	//printf("stmt\n");
	/*printf("stmt->");
	node * p = n->child;
		while(p){
			printf("%s:%s ",p->name,p->val);
			p=p->sibling;
		}
		printf("\n");*/
	if(!n || !n->child) return;
	//else printf("%s\n", n->child->name);
	if(strcmp(n->child->name, "Exp")==0){// Stmt->Exp SEMI
		//printf("stmt->exp;\n");
		Exp(n->child);
	}
	else if(strcmp(n->child->name, "CompSt")==0){// Stmt->CompSt
		//printf("stmt->compst\n");
		layer++;
		LayerList l = (LayerList)malloc(sizeof(struct LayerList_));
		l->layer = layer;
		if(!layerlist) layerlist = l;
		else{
			l->next = layerlist;
			layerlist = l;
		}
		CompSt(n->child, f);
		pop_layer();
		layer--;
	}
	else if(strcmp(n->child->name, "RETURN")==0){// Stmt->RETURN Exp SEMI;
		//printf("stmt->return exp;\n");
		Type t = Exp(n->child->sibling);
		if(!check_type(f->ret_type, t)){
			error = true;
			printf("Error Type 8 at Line %d: Type mismatched for return\n", n->child->line);
		}
	}
	else if(strcmp(n->child->name, "IF")==0){// Exp->IF LP Exp RP Stmt (ELSE Stmt)
		//printf("stmt->if...\n");
		node* tmp = n->child->sibling->sibling;
		Exp(tmp);
		tmp = tmp->sibling->sibling;
		Stmt(tmp, f);
		if(tmp->sibling){
			Stmt(tmp->sibling->sibling, f);
		}
	}
	else if(strcmp(n->child->name, "WHILE")==0){// Exp->WHILE LP Exp RP Stmt
		//printf("stmt->while...\n");
		Exp(n->child->sibling->sibling);
		Stmt(n->child->sibling->sibling->sibling->sibling, f);
	}
	/*else{
		printf("something wrong in stmt!!!\n");
		node * p = n->child;
		while(p){
			printf("%s:%s ",p->name,p->val);
			p=p->sibling;
		}
		printf("\n");
	}*/
	//printf("Stmt end\n");
}

FieldList DefList(node* n, bool is_struct)
{// DefList->Def DefList
	//printf("deflist\n");
	if(!n->child) return NULL;
	if(strcmp(n->name, "DefList")!=0) return NULL;
	if(n && n->child){
	//	printf("%s, has child\n", n->name);
		if(is_struct){
			//printf("1\n");
			FieldList f = Def(n->child, is_struct);
			//printf("2\n");
			FieldList p = f;	// int a,b,c;
			//printf("3\n");
			if(!p) return NULL;
			//printf("4\n");
			while(p->next){
				p = p->next;
			}
			//printf("5\n");
			p->next = DefList(n->child->sibling, is_struct);
			//printf("6\n");
			return f;
		}
		else{
			Def(n->child, is_struct);
			DefList(n->child->sibling, is_struct);
		}
	}
	//printf("end deflist\n");
	return NULL;
}

FieldList Def(node* n, bool is_struct)
{// Def->Specifier DecList SEMI
	//FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
	//printf("def\n");
	if(is_struct){
		Type type = Specifier(n->child);
	//	printf("next declist\n");
		if(!type) return NULL;
		return DecList(n->child->sibling, type, is_struct);
	}
	else{
		Type type = Specifier(n->child);
		if(!type) return NULL;	// TYPE ERROR!!!
		DecList(n->child->sibling, type, is_struct);
	}
	return NULL;
}

FieldList DecList(node* n, Type t, bool is_struct)
{// DecList->Dec | Dec COMMA DecList
	//printf("declist\n");
	FieldList f = Dec(n->child, t, is_struct);
	if(n->child->sibling){ // DecList->Dec COMMA DecList
		if(f && is_struct){
			f->next = DecList(n->child->sibling->sibling, t, is_struct);
		}
		else if(!is_struct){
				DecList(n->child->sibling->sibling, t, is_struct);
		}
	}
	return f;
}

FieldList Dec(node* n, Type t, bool is_struct)
{
	//printf("dec\n");
	if(n->child->sibling){//Dec->VarDec ASSIGNOP Exp
		if(is_struct){
			error = true;
			printf("Error Type 15 at Line %d: Illegal Field Initialization\n", n->child->sibling->line);
		}
		else{
			FieldList f = VarDec(n->child, t, is_struct);
			if(f){
				Type t = Exp(n->child->sibling->sibling);
				if(!check_type(f->type, t)){
					//printf("f->name:%s\n",f->name);
					error = true;
					printf("Error Type 5 at Line %d: Type mismatched for assigenment\n", n->child->sibling->line);
				}
			}
			return NULL;
		}
	}
	else{//Dec->VarDec
		if(is_struct){
			return VarDec(n->child, t, is_struct);
		}
		else{
			VarDec(n->child, t, is_struct);
		}
	}
	return NULL;
}

Type Exp(node* n)
{
	//printf("Exp\n");
	if(strcmp(n->child->name,"Exp")==0){
		if(strcmp(n->child->sibling->name, "ASSIGNOP")==0){// Exp->Exp ASSIGNOP Exp
			//printf("exp->exp=exp\n");
			Type t1 = Exp(n->child);
			Type t2 = Exp(n->child->sibling->sibling);
			if(!t1 || !t2) return NULL;
			if(!check_left(n->child)){
				error = true;
				printf("Error Type 6 at line %d: The left-hand side of an assignment must be a variable\n",n->child->line);
				return NULL;
			}
			//printf("check left end\n");
			/*if(t2->kind==ARRAY){
				printf("here\n");
				if(!t2->u.array.elem) printf("error array elem null\n");
			}*/
			if(!check_type(t1, t2)){
				error = true;
				printf("Error Type 5 at Line %d: Type mismatched for assigenment\n", n->child->sibling->line);
				return NULL;
			}
			//printf("exp assignop end\n");
			return t1;
		}
		else if(strcmp(n->child->sibling->name, "AND")==0 || strcmp(n->child->sibling->name, "OR")==0){// Exp->Exp AND Exp || Exp OR Exp
			//printf("exp=>exp and/or exp\n");
			Type t1 = Exp(n->child);
			Type t2 = Exp(n->child->sibling->sibling);
			if(!t1 || !t2) return NULL;
			if(!check_type(t1, t2)){
				error = true;
				printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->sibling->line);
				return NULL;
			}
			if(t1->u.basic == INT && t2->u.basic == INT){// only int, int can do and
				return t1;
			}
			else{
				error = true;
				printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->sibling->line);
				return NULL;
			}
		}
		//else if(strcmp(n->child->sibling->name, "OR")==0) same as and
		else if(strcmp(n->child->sibling->name, "RELOP")==0){// Exp->Exp RELOP Exp
			//printf("exp->exp relop exp\n");
			Type t1 = Exp(n->child);
			Type t2 = Exp(n->child->sibling->sibling);
			if(!t1 || !t2) return NULL;
			if(!check_type(t1, t2)){
				error = true;
				printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->sibling->line);
				return NULL;
			}
			if(t1->kind == BASIC){
				Type t = (Type)malloc(sizeof(struct Type_));
				t->kind = BASIC;
				t->u.basic = INT;
				return t;
			}
			else{
				error = true;
				printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->sibling->line);
				return NULL;
			}
		}
		else if(strcmp(n->child->sibling->name, "PLUS")==0 ||strcmp(n->child->sibling->name, "MINUS")==0 || 
		strcmp(n->child->sibling->name, "STAR")==0 || strcmp(n->child->sibling->name, "DIV")==0) {// Exp->Exp PLUS/MINUS/STAR/DIV EXP
			//printf("exp->exp +/-/*/div exp\n");
			Type t1 = Exp(n->child);
			Type t2 = Exp(n->child->sibling->sibling);
			if(!t1 || !t2) return NULL;
			if(!check_type(t1, t2)){
				error = true;
				printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->sibling->line);
				return NULL;
			}
			if(t1->kind == BASIC){
				return t1;
			}
			else{
				error = true;
				printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->sibling->line);
				return NULL;
			}
		}
		else if(strcmp(n->child->sibling->name, "LB")==0){// Exp->Exp LB Exp RB, array
			//printf("exp->exp[exp]\n");
			Type t1 = Exp(n->child);
			if(!t1) return NULL;
			if(t1->kind!=ARRAY){
				error = true;
				printf("Error Type 10 at Line %d: This is not an array\n", n->child->line);
				return NULL;
			}
			Type t2 = Exp(n->child->sibling->sibling);
			if(!t2) return NULL;
			if(t2->kind==BASIC && t2->u.basic==INT){
				return t1->u.array.elem;
			}
			else{
				error = true;
				printf("Error Type 12 at Line %d: inside [] is not an integer\n", n->child->sibling->sibling->line);
				return NULL;
			}
		}
		else{// Exp->Exp DOT ID, struct.id
			//printf("exp->exp.id\n");
			Type t = Exp(n->child);
			if(!t) return NULL;
			if(t->kind!=STRUCTURE){
				error = true;
				printf("Error Type 13 at Line %d: Illegal use of \".\"\n", n->child->sibling->line);
				return NULL;
			}
			FieldList p = t->u.structure;
			while(p){
				if(strcmp(p->name, n->child->sibling->sibling->val)==0){
					return p->type;
				}
				p = p->next;
			}
			error = true;
			printf("Error Type 14 at Line %d: Non-existent field \"%s\"\n", n->child->sibling->sibling->line,
			n->child->sibling->sibling->val);
			return NULL;
		}
	}
	else if(strcmp(n->child->name, "LP")==0){// Exp->LP Exp RP
		//printf("exp->(exp)\n");
		return Exp(n->child->sibling);
	}
	else if(strcmp(n->child->name, "MINUS")==0){// Exp->MINUS Exp
		//printf("exp->-exp\n");
		Type t = Exp(n->child->sibling);
		if(!t) return NULL;
		if(t->kind == BASIC){
			return t;
		}
		else{
			error = true;
			printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->line);
			return NULL;
		}
	}
	else if(strcmp(n->child->name, "NOT")==0){// Exp->NOT Exp
		//printf("exp->~exp\n");
		Type t = Exp(n->child->sibling);
		if(!t) return NULL;
		if(t->kind == BASIC && t->u.basic == INT){
			Type t1 = (Type)malloc(sizeof(struct Type_));
			t1->kind = BASIC;
			t1->u.basic = INT;
			return t1;
		}
		else{
			error = true;
			printf("Error Type 7 at Line %d: Type mismatched for operands\n", n->child->line);
			return NULL;
		}
	}
	else if(strcmp(n->child->name, "ID")==0){
		if(!n->child->sibling){// Exp->ID, var
			//printf("exp id: %s\n", n->child->val);
			HashNode h = find(n->child->val);
			if(!h){
				error = true;
				printf("Error Type 1 at Line %d: Undefined variable \"%s\"\n", n->child->line, n->child->val);
				return NULL;
			}
			return h->type;
		}
		else if(strcmp(n->child->sibling->sibling->name, "Args")==0){// Exp->ID LP Args RP, func
			//printf("exp->func(args)\n");
			HashNode h = find(n->child->val);
			if(!h){
				error = true;
				printf("Error Type 2 at Line %d: Undefined function \"%s\"\n", n->child->line, n->child->val);
				return NULL;
			}
			else if(h->type->kind!=FUNCTION){
				error = true;
				printf("Error Type 11 at Line %d: \"%s\" is not a function\n", n->child->line, n->child->val);
				return NULL;
			}
			if(!Args(n->child->sibling->sibling, h->type->u.func->param, h->name)){
				error = true;
				printf("Error Type 9 at Line %d: Function \"%s\" is not applicable for arguments\n", n->child->line, h->name);
				return NULL;
			}
			else return h->type->u.func->ret_type;
		}
		else{// Exp->ID LP RP, func
			//printf("exp->func()\n");
			HashNode h = find(n->child->val);
			if(!h){
				error = true;
				printf("Error Type 2 at Line %d: Undefined function \"%s\"\n", n->child->line, n->child->val);
				return NULL;
			}
			else if(h->type->kind!=FUNCTION){
				error = true;
				printf("Error Type 11 at Line %d: \"%s\" is not a function\n", n->child->line, n->child->val);
				return NULL;
			}
			else if(h->type->u.func->param!=NULL){
				error = true;
				printf("Error Type 9 at Line %d: Function \"%s\"() is not applicable for arguments\n", n->child->line, n->child->val);
				return NULL;
			}
			return h->type->u.func->ret_type;
		}
	}
	else if(strcmp(n->child->name, "INT")==0){// Exp->INT
		//printf("exp->int\n");
		Type t = (Type)malloc(sizeof(struct Type_));
		t->kind = BASIC;
		t->u.basic =INT;
		return t;
	}
	else if(strcmp(n->child->name, "FLOAT")==0){// Exp->FLOAT
		//printf("exp->float\n");
		Type t = (Type)malloc(sizeof(struct Type_));
		t->kind = BASIC;
		t->u.basic = FLOAT;
		return t;
	}
	//printf("something wrong in Exp??? %s\n",n->child->name);
	return NULL;
}

bool check_left(node* n)
{
	//printf("check left\n");
	if(!n) return true;	// already reported fault
	if(!n->child) return false;
	if(!n->child->sibling && strcmp(n->child->name, "ID")==0){
		// ID and no more siblings
		return true;
	}
	if(!n->child->sibling) return false;
	if(strcmp(n->child->sibling->name, "LB")==0 || strcmp(n->child->sibling->name, "DOT")==0){
		// Exp LB Exp RB || Exp DOT ID
		return true;
	}
	//printf("check left false, %s:%s\n", n->name, n->val);
	return false;
}

bool check_type(Type t1, Type t2)
{
	//printf("check type\n");
	if(!t1 || !t2){
		//printf("error check type null!!!\n");
		return false;
	}
	if(t1->kind == t2->kind){
		//printf("t1 kind = t2 kind\n");
		if(t1->kind == BASIC){
			//printf("basic\n");
			return t1->u.basic==t2->u.basic;
		}
		else if(t1->kind == ARRAY){
			// arrays are same type if have same dimension
			//printf("array\n");
			int d1 = 0, d2 = 0;
			Type tmp1 = t1->u.array.elem;
			Type tmp2 = t2->u.array.elem;
			//printf("here\n");
			while(tmp1 && tmp1->kind==ARRAY){// last is not array
				d1++;
				tmp1 = tmp1->u.array.elem;
			}
			while(tmp2 && tmp2->kind==ARRAY){
				d2++;
				tmp2 = tmp2->u.array.elem;
			}
			return d1==d2;
		}
		else if(t1->kind == STRUCTURE){
			//printf("structure\n");
			if(strlen(t1->u.structure->name)==0 && strlen(t2->u.structure->name)==0){
				return t1->u.structure->id == t2->u.structure->id;
			}
			return strcmp(t1->u.structure->name, t2->u.structure->name)==0;
		}
		/*else{
			printf("check type error!!!!!\n");
		}*/
	}
	//printf("t1 kind != t2 kind\n");
	return false;
}

HashNode find(char* val)
{	
	//printf("find %s\n",val);
	unsigned int pos = hash_pjw(val);
	HashNode t = table[pos];
	//if(!t) printf("t null\n");
	while(t){
		//printf("t:%s\n",t->name);
		if(strcmp(t->name, val)==0) return t;
		t = t->next;
	}
	return NULL;
}

bool Args(node* n, FieldList param, char * funcname){// Args->Exp COMMA Args | Exp
	//printf("args\n");
	if(!param && !n) return true;
	else if(!param || !n) return false;
	Type t = Exp(n->child);
	if(!check_type(t, param->type)){
		//printf("check type false\n");
		//printf("Error Type 9 at Line %d: Function \"%s\" is not applicable for arguments\n", n->child->line, funcname);
		return false;
	}
	if(!n->child->sibling){
		//printf("last one\n");
		if(!param->next) return true;
		else return false;
	}
	if(n->child->sibling){
		return Args(n->child->sibling->sibling, param->next, funcname);
	}
}