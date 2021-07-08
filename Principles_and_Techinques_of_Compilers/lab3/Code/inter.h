#ifndef INTER
#define INTER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "hash.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodes_* InterCodes;
typedef enum{EQ,LS,LE,GR,GE,NE} Relop;
typedef struct vNode_* vNode;
typedef struct ArgList_* ArgList;
typedef struct StructNode_* StructNode;
typedef struct myOffset_* myOffset;

struct Operand_
{
    enum { VARIABLE, CONSTANT, TEMP, ADDRESS, FUNC, LABEL, VADDR, TADDR, STAR } kind;
    union{
        int var_no;
        int val;
        int label_no;
        int temp_no;
        char* fname;
        Operand op; //star
    } u;
    char* name;
    Type t;
};

struct InterCode_
{
    enum { ASSIGN, ADD, SUB, MUL, DIV, FUNCDEC, PARAM, RETURN, RELOP, GOTO, LABELDEC, CALL, READ, WRITE, ARG, DEC, ADDR } kind;
    union{
        Operand op; // funcdec, param, return， goto, read
        struct { Operand right, left; } assign; // assign , call, addr
        struct { Operand result, op1, op2; } binop; // +-*/, 
        struct { Operand op1, op2, go; Relop rp;} rlp; // relop
        struct { Operand op; int size; } dec;
    } u;
};

struct InterCodes_
{
    InterCode code;
    InterCodes next;
};

struct vNode_
{
    char* name;
    int var_no;
    Operand op;
    vNode next;
};

struct ArgList_
{
    Operand op;
    ArgList next;
};

struct StructNode_
{
    char* name;
    StructNode next;
};

struct myOffset_
{
    int offset;
    Type t;
};

Operand cVar(char* s, Type t);
Operand cConstant(int val);
Operand cLabel();
Operand cTemp();
Operand cFunc(char* s);
Operand cStar(Operand op, Type t);
void insertInterCode(InterCode ic);
void insertStructNode(StructNode s);
void insertVNode(vNode v);
Operand iParam(char* s, Type t);
void iFunDec(char* s);
void iReturn(Operand op);
void iRelop(Operand op1, Operand op2, Relop relop, Operand go);
void iGoto(Operand go);
void iLabel(Operand l);
void iAssign(Operand left, Operand right);
void iCalculate(Operand t, Operand op1, Operand op2, int type); //+:1, -:2, *:3, /:4
void iRead(Operand t);
void iCall(Operand t, Operand f);
void iWrite(Operand op);
void iArg(Operand arg);
void iDec(Operand op, int size);
void iAddr(Operand op1, Operand op2);

Operand findVar(char* s);
int getSize(Type t);
bool paramStruct(char* s);
myOffset getOffset(char* s, FieldList f);

void writeFile(char* filename);
void writeOp(Operand op, FILE* f);
void writeRelop(Relop r, FILE* f);

void translate(node* root);
void transExtDefList(node* n);
void transExtDef(node* n);

Type transSpecifier(node* n);
Type transStructSpecifier(node* n);

Operand transVarDec(node* n, Type t, bool isParam, int arrayNum);
void transFunDec(node* n);
void transVarList(node* n);
void transParamDec(node* n);

void transCompSt(node* n);
void transStmtList(node* n);
void transStmt(node* n);

void transDefList(node* n);
void transDef(node* n);
void transDecList(node* n, Type t);
void transDec(node* n, Type t);

Operand transExp(node* n);
void transCond(node* n, Operand labelT, Operand labelF);

void insertArg(ArgList arg);
void transArgs(node* n);
Relop getRelop(node* n);
#endif
