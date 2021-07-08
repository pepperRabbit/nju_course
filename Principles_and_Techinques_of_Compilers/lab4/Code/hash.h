#ifndef HASH
#define HASH

#include "tree.h"
//#include "inter.h"
#include <stdlib.h>
#define HASHNUM 16384
#define INT 1
#define FLOAT 2

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Function_* Function;
typedef struct HashNode_* HashNode;
typedef struct LayerList_* LayerList;
typedef struct LayerListNode_* LayerListNode;

enum Kind { BASIC, ARRAY, STRUCTURE, FUNCTION };

struct Type_
{
	enum Kind kind;
	union
	{
		int basic;	// basic
		struct { Type elem; int size; } array;	// array info
		FieldList structure; // struct info
		Function func;
	} u;
};

struct FieldList_
{
	char* name;
	Type type;
	FieldList next;
	int line;
	int id;
};

struct Function_
{
	char *name;
	Type ret_type;
	FieldList param;
};

struct HashNode_
{
	char* name;
	Type type;
	HashNode next;
	int layer;
};

struct LayerList_
{
	int layer;
	LayerListNode node;
	LayerList next;
};

struct LayerListNode_
{
	HashNode hashnode;
	LayerListNode next;
};

unsigned int hash_pjw(char* name);
void init();
void analyze(node* root);
void ExtDefList(node* n);
void ExtDef(node* n);
void ExtDecList(node* n, Type t);

Type Specifier(node* n);
Type StructSpecifier(node* n);

FieldList VarDec(node* n, Type t, bool is_struct, bool is_param);
Function FunDec(node* n);
FieldList VarList(node* n);
FieldList ParamDec(node* n);

void CompSt(node* n, Function f);
void StmtList(node* n, Function f);
void Stmt(node* n, Function f);

FieldList DefList(node* n, bool is_struct);
FieldList Def(node* n, bool is_struct);
FieldList DecList(node* n, Type t, bool is_struct);
FieldList Dec(node* n, Type t, bool is_struct);

Type Exp(node* n);
bool Args(node* n, FieldList param, char * funcname);

HashNode find(char* val);
bool check_redefined(Type t);
void insert(char* s, Type t);
bool check_left(node* n);
bool check_type(Type t1, Type t2);
void pop_layer();
#endif
