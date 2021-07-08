#ifndef MIPS
#define MIPS

#include "inter.h"

typedef struct Var_* Var;
typedef struct Register_* Register;

struct Var_
{
    char* name;
    int reg;
    int offset;
    Var next;
};

struct Register_
{
    char* name;
    int used;
    int constant;
    Var var;
};

void initRegister();
void toMips(InterCodes ic, char* filename);
InterCodes nextBlock(InterCodes ic);
int getReg(FILE* f, Operand op);
void insertVar(Var v);
Var findVar1(char* name);
void writeReadWrite(FILE* f);
void mipsAssign(FILE* f, InterCode ic);
void mipsFuncdec(FILE* f, InterCode ic);
void mipsArg(FILE* f, InterCode ic);
void mipsParam(FILE* f, InterCode ic, int param);
void mipsReturn(FILE* f, InterCode ic);
void mipsRelop(FILE* f, InterCode ic);
void mipsGoto(FILE* f, InterCode ic);
void mipsCalculation(FILE* F, InterCode ic);
void mipsRead(FILE* f, InterCode ic);
void mipsWrite(FILE* f, InterCode ic);
void mipsCall(FILE* f, InterCode ic);
void mipsLabel(FILE* f, InterCode ic);
void mipsDec(FILE* f, InterCode ic);
void mipsAddr(FILE* f, InterCode ic);
void clearReg(FILE* f, int i);
#endif
