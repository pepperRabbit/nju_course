#include "mips.h"

extern Var varlist;
struct Register_ regs[32];
char* names[] = {
    "$zero", "$at",
	"$v0", "$v1",
	"$a0", "$a1", "$a2", "$a3",
	"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
	"$t8", "$t9",
	"$k0", "$k1",
	"$gp", "$sp", "$fp", "$ra"
};

int paramNo = 0;
int argsNo = 0;
int spOffset = 0;
int stack = 200;

void initRegister()
{
    for(int i=0; i<32; i++) {
        regs[i].name = names[i];
        regs[i].used = 0;
        regs[i].constant = 0;
        regs[i].var = NULL;
    }
}

int getReg(FILE* f, Operand op)
{
    int i;
    for(i=8; i<=15; i++) {
        if(regs[i].used == 0) {
            regs[i].used = 1;
            break;
        }
    }
    /*if(i>15) {
        printf("reg full\n");
        exit(1);
    }*/
    if(op->kind == CONSTANT) {
        regs[i].constant = 1;
        fprintf(f,"  li %s, %d\n", regs[i].name, op->u.val);
        return i;
    }
    char tmp[32];
    memset(tmp, 0, sizeof(tmp));
    if(op->kind == TEMP) {
        sprintf(tmp, "t%d", op->u.temp_no);
    }
    else if(op->kind == VARIABLE) {
        sprintf(tmp, "v%d", op->u.var_no);
    }
    else if(op->kind == STAR) {
        if(op->u.op->kind == TEMP) {
            sprintf(tmp,"t%d", op->u.op->u.temp_no);
        }
        else if(op->u.op->kind == VARIABLE) {
            sprintf(tmp,"v%d", op->u.op->u.var_no);
        }
        /*else {
            printf("star error\n");
            exit(1);
        }*/
    }
    //printf("getreg op: %s\n", tmp);
    Var v = findVar1(tmp);
    if(v) {
        regs[i].var = v;
        v->reg = i;
        //printf("var not null, ");
        //printf("lw %s, %d($fp)\n", regs[i].name, v->offset);
        fprintf(f, "  lw %s, %d($fp)\n", regs[i].name, v->offset);
        /*if(op->kind == STAR) {
            fprintf(f, "lw %s, 0(%s)\n", regs[i].name, regs[i].name);
        }*/
    }
    else {
        //printf("var null\n");
        v = (Var)malloc(sizeof(struct Var_));
        spOffset -= 4;
        //v->name = tmp; 卧槽
        v->name = (char*)malloc(sizeof(char)*strlen(tmp)+1);
        strcpy(v->name, tmp);
        v->offset = spOffset;
        v->reg = i;
        regs[i].var = v;
        insertVar(v);
    }
    return i;
}

void insertVar(Var v)
{
    if(!varlist) {
        varlist = v;
    }
    else {
        v->next = varlist;
        varlist = v;
    }
}

Var findVar1(char* name)
{
    Var p = varlist;
    //printf("findvar %s\n", name);
    while(p) {
        //printf("%s\n", p->name);
        if(strcmp(name, p->name)==0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void toMips(InterCodes ic, char* filename)
{
    initRegister();
    InterCodes p = ic;
    if(!filename) {
        printf("filename empty\n");
        return;
    }
    FILE* f = fopen(filename, "w");
    if(!f) {
        printf("f null\n");
        return;
    }
    writeReadWrite(f);
    bool firstParam = true;
    int param = 0;
    while(p) {
        InterCodes next = nextBlock(p->next);
        while(p!=next) {
            switch(p->code->kind) {
                case ASSIGN:
                    //printf("assign\n");
                    mipsAssign(f, p->code);
                    break;
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                    //printf("calculate\n");
                    mipsCalculation(f, p->code);
                    break;
                case FUNCDEC:
                    //printf("fundec\n");
                    mipsFuncdec(f, p->code);
                    break;
                case ARG:
                    //printf("arg\n");
                    mipsArg(f, p->code);
                    break;
                case PARAM:
                    if(firstParam) {
                        firstParam = false;
                        InterCodes t = p->next;
                        while(t->code->kind==PARAM) {
                            param++;
                            t = t->next;
                        }
                    }
                    //printf("param num %d\n", param);
                    mipsParam(f, p->code, param);
                    if(p->next->code->kind!=PARAM) {
                        firstParam = true;
                        param = 0;
                    }
                    break;
                case RETURN:
                    //printf("return\n");
                    mipsReturn(f, p->code);
                    break;
                case RELOP:
                    //printf("relop\n");
                    mipsRelop(f, p->code);
                    break;
                case GOTO:
                    //printf("goto\n");
                    mipsGoto(f, p->code);
                    break;
                case LABELDEC:
                    //printf("labeldec\n");
                    mipsLabel(f, p->code);
                    break;
                case CALL:
                    //printf("call\n");
                    mipsCall(f, p->code);
                    break;
                case READ:
                    //printf("read\n");
                    mipsRead(f, p->code);
                    break;
                case WRITE:
                    //printf("write\n");
                    mipsWrite(f, p->code);
                    break;
                case DEC:
                    //printf("dec\n");
                    mipsDec(f, p->code);
                    break;
                case ADDR:
                    //printf("addr\n");
                    mipsAddr(f, p->code);
                    break;
            }
            p = p->next;
        }
    }
    fclose(f);
}

void mipsAssign(FILE* f, InterCode ic)
{
    Operand op1 = ic->u.assign.left;
    Operand op2 = ic->u.assign.right;
    int reg1 = getReg(f, op1);
    if(op1->kind!=STAR) {
        if(op2->kind == CONSTANT) {
            // x=#k, li reg(x), k
            fprintf(f, "  li %s, %d\n", names[reg1], op2->u.val);
        }
        else if(op2->kind == TEMP || op2->kind == VARIABLE) {
            // x=y, move reg(x), reg(y)
            int reg2 = getReg(f, op2);
            fprintf(f, "  move %s, %s\n", names[reg1], names[reg2]);
        }
        else if(op2->kind == STAR) {
            // x=*y, lw reg(x), 0(reg(y))
            int reg2 = getReg(f, op2);
            fprintf(f, "  lw %s, 0(%s)\n", names[reg1], names[reg2]);
        }
        /*else {
            printf("assign op2 kind error1:%d\n", op2->kind);
            exit(1);
        }*/
    }
    else {
        if(!(op2->kind == TEMP || op2->kind == VARIABLE || op2->kind == CONSTANT || op2->kind == STAR)) {
            printf("assign op2 kind error2:%d\n", op2->kind);
            exit(1);
        }
        // *x=y, sw reg(y), 0(reg(x))
        if(op2->kind == CONSTANT) {
            fprintf(f, "  li $s1, %d\n", op2->u.val);
            fprintf(f, "  sw $s1, 0(%s)\n", names[reg1]);
        }
        else if(op2->kind == STAR) {
            // *x=*y...
            int reg2 = getReg(f, op2);
            fprintf(f,"  lw $s1, 0(%s)\n", names[reg2]);
            fprintf(f,"  sw $s1, 0(%s)\n", names[reg1]);
        }
        else {
            int reg2 = getReg(f, op2);
            fprintf(f, "  sw %s, 0(%s)\n", names[reg2], names[reg1]);
        }
    }
    clearReg(f, reg1);
}

void mipsCalculation(FILE* f, InterCode ic)
{
    Operand res = ic->u.binop.result;
    Operand op1 = ic->u.binop.op1;
    Operand op2 = ic->u.binop.op2;
    //printf("calculate res:%d, op1:%d, op2:%d\n", res->kind, op1->kind, op2->kind);
    int reg1 = getReg(f, res);
    int reg2 = getReg(f, op1);
    int reg3 = getReg(f, op2);
    /* 也是没考虑star，无语
    switch(ic->kind) {
        case ADD:
            fprintf(f, "  add %s, %s, %s\n", names[reg1], names[reg2], names[reg3]);
            break;
        case SUB:
            fprintf(f, "  sub %s, %s, %s\n", names[reg1], names[reg2], names[reg3]);
            break;
        case MUL:
            fprintf(f, "  mul %s, %s, %s\n", names[reg1], names[reg2], names[reg3]);
            break;
        case DIV:
            fprintf(f, "  div %s, %s\n", names[reg2], names[reg3]);
            fprintf(f, "  mflo %s\n", names[reg1]);
            break;
    }*/
    char r1[20], r2[20], r3[20];
    memset(r1, 0, sizeof(r1));
    memset(r1, 0, sizeof(r2));
    memset(r1, 0, sizeof(r3));
    if(res->kind==STAR) {
        fprintf(f, "  lw $s1, 0(%s)\n", names[reg1]);
        strcpy(r1, "$s1");
    }
    else {
        strcpy(r1, names[reg1]);
    }
    if(op1->kind==STAR) {
        fprintf(f, "  lw $s2, 0(%s)\n", names[reg2]);
        strcpy(r2, "$s2");
    }
    else{
        strcpy(r2, names[reg2]);
    }
    if(op2->kind==STAR) {
        fprintf(f, "  lw $s3, 0(%s)\n", names[reg3]);
        strcpy(r3, "$s3");
    }
    else{
        strcpy(r3, names[reg3]);
    }
    switch(ic->kind) {
        case ADD:
            fprintf(f, "  add %s, %s, %s\n", r1, r2, r3);
            break;
        case SUB:
            fprintf(f, "  sub %s, %s, %s\n", r1, r2, r3);
            break;
        case MUL:
            fprintf(f, "  mul %s, %s, %s\n", r1, r2, r3);
            break;
        case DIV:
            fprintf(f, "  div %s, %s\n", r2, r3);
            fprintf(f, "  mflo %s\n", r1);
            break;
    }
    clearReg(f, reg1);
}

//-fundec -param -calcul -assign -ret -labeldec -goto -relop -arg -call
//fundec ret param arg

void mipsFuncdec(FILE* f, InterCode ic)
{
    //printf("fundec\n");
    spOffset = 0;
    paramNo = 0;
    fprintf(f, "\n%s:\n", ic->u.op->u.fname);
    fprintf(f, "  addi $sp, $sp, -4\n");
	fprintf(f, "  sw $fp, 0($sp)\n");
	fprintf(f, "  move $fp, $sp\n");
    fprintf(f, "  subu $sp, $sp, %d\n", stack);
}

void mipsArg(FILE* f, InterCode ic)
{
    char tmp[32];
    memset(tmp, 0, sizeof(tmp));
    Operand op = ic->u.op;
    Var arg;
    if(op->kind == TEMP || op->kind == VARIABLE) {
        if(op->kind == TEMP) {
            sprintf(tmp,"t%d", op->u.temp_no);
        }
        else {
            sprintf(tmp,"v%d", op->u.var_no);
        }
        arg = findVar1(tmp);
        if(!arg) {
            printf("arg null\n");
            exit(1);
        }
        if(argsNo<4) {
            fprintf(f, "  lw $a%d, %d($fp)\n", argsNo, arg->offset);
        }
        else {
            fprintf(f, "  lw $s0, %d($fp)\n", arg->offset);
            fprintf(f, "  subu $sp, $sp, 4\n");
            fprintf(f, "  sw $s0, 0($sp)\n");
            
        }
    }
    else if(op->kind == STAR) {
        if(op->u.op->kind == TEMP) {
            sprintf(tmp,"t%d", op->u.op->u.temp_no);
        }
        else if(op->u.op->kind == VARIABLE) {
            sprintf(tmp,"v%d", op->u.op->u.var_no);
        }
        /*else {
            printf("star error\n");
            exit(1);
        }*/
        arg = findVar1(tmp);
        if(!arg) {
            printf("arg null\n");
            exit(1);
        }
        fprintf(f, "  lw $s1, %d($fp)\n", arg->offset);
        if(argsNo<4) {
            fprintf(f, "  lw $a%d, 0($s1)\n", argsNo);
        }
        else {
            fprintf(f, "  lw $s0, 0($s1)\n");
            fprintf(f, "  subu $sp, $sp, 4\n");
            fprintf(f, "  sw $s0, 0($sp)\n");
        }
    }
    else if(op->kind == CONSTANT) {
        if(argsNo<4) {
            fprintf(f, "  li $a%d, %d\n", argsNo, op->u.val);
        }
        else {
            fprintf(f, "  li $s0, %d\n", op->u.val);
            fprintf(f, "  subu $sp, $sp, 4\n");
            fprintf(f, "  sw $s0, 0($sp)\n");
        }
    }
    /*else {
        printf("arg type error:%d\n", op->kind);
        exit(1);
    }*/
    argsNo++;
}

void mipsParam(FILE* f, InterCode ic, int paramNum)
{
    if(ic->u.op->kind!=VARIABLE) {
        printf("param type error %d\n", ic->u.op->kind);
        exit(1);
    }
    spOffset -= 4;
    char tmp[32];
    memset(tmp, 0, sizeof(tmp));
    Operand op = ic->u.op;
    sprintf(tmp, "v%d" , op->u.var_no);
    Var v = (Var)malloc(sizeof(struct Var_));
    v->name = (char*)malloc(sizeof(char)*strlen(tmp)+1);
    strcpy(v->name, tmp);
    v->offset = spOffset;
    insertVar(v);
    if(paramNum<4) {
        fprintf(f, "  sw $a%d, %d($fp)\n", paramNo, v->offset);
    }
    else {
        int no = paramNum - paramNo;
        //printf("param %d\n", no);
        if(no<4) {// 0 1 2 3 4 5
            //printf("  sw $a%d, %d($fp)\n", no, v->offset);
            fprintf(f, "  sw $a%d, %d($fp)\n", no, v->offset);
        }
        else {
            //printf("  lw $t8, %d($fp)\n  sw $t8, %d($fp)\n", (paramNo+2)*4, v->offset);
            fprintf(f, "  lw $t8, %d($fp)\n", (paramNo+2)*4);
            fprintf(f, "  sw $t8, %d($fp)\n", v->offset);
        }
    }
    paramNo++;
}

void mipsReturn(FILE* f, InterCode ic)
{
    Operand op = ic->u.op;
    if(op->kind == CONSTANT) {
        fprintf(f, "  li $v0, %d\n", op->u.val);
    }
    else {
        int reg1 = getReg(f, op);
        fprintf(f, "  move $v0, %s\n", names[reg1]);
        clearReg(f, reg1);
    }
    fprintf(f, "  addi $sp, $sp, %d\n", stack);
    fprintf(f, "  lw $fp, 0($sp)\n");
    fprintf(f, "  addi $sp, $sp, 4\n");
    fprintf(f, "  jr $ra\n");
}

void mipsRelop(FILE* f, InterCode ic)
{
    Operand op1 = ic->u.rlp.op1;
    Operand op2 = ic->u.rlp.op2;
    Relop rp = ic->u.rlp.rp;
    Operand go = ic->u.rlp.go;
    if(go->kind!=LABEL) {
        printf("relop label error %d\n", go->kind);
        exit(1);
    }
    /* 没考虑star，无语
    int reg1 = getReg(f, op1);
    int reg2 = getReg(f, op2);
    switch(rp) {
        case EQ:
            fprintf(f, "  beq %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
            break;
        case LS:
            fprintf(f, "  blt %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
            break;
        case LE:
            fprintf(f, "  ble %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
            break;
        case GR:
            fprintf(f, "  bgt %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
            break;
        case GE:
            fprintf(f, "  bge %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
            break;
        case NE:
            fprintf(f, "  bne %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
            break;
    }*/
    if(op1->kind==CONSTANT && op2->kind==CONSTANT) {
        int reg1 = getReg(f, op1);
        int reg2 = getReg(f, op2);
        switch(rp) {
            case EQ:
                fprintf(f, "  beq %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
                break;
            case LS:
                fprintf(f, "  blt %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
                break;
            case LE:
                fprintf(f, "  ble %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
                break;
            case GR:
                fprintf(f, "  bgt %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
                break;
            case GE:
                fprintf(f, "  bge %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
                break;
            case NE:
                fprintf(f, "  bne %s, %s, label%d\n", names[reg1], names[reg2], go->u.label_no);
                break;
        }
    }
    else if(op1->kind!=CONSTANT && op2->kind!=CONSTANT) {
        int reg1 = getReg(f, op1);
        int reg2 = getReg(f, op2);
        char r1[20];
        char r2[20];
        memset(r1, 0, sizeof(r1));
        memset(r2, 0, sizeof(r2));
        if(op1->kind==STAR) {
            fprintf(f, "  lw $s1, 0(%s)\n", names[reg1]);
            strcpy(r1, "$s1");
        }
        else {
            strcpy(r1, names[reg1]);
        }
        if(op2->kind==STAR) {
            fprintf(f, "  lw $s2, 0(%s)\n", names[reg2]);
            strcpy(r2, "$s2");
        }
        else {
            strcpy(r2, names[reg2]);
        }
        switch(rp) {
            case EQ:
                fprintf(f, "  beq %s, %s, label%d\n", r1, r2, go->u.label_no);
                break;
            case LS:
                fprintf(f, "  blt %s, %s, label%d\n", r1, r2, go->u.label_no);
                break;
            case LE:
                fprintf(f, "  ble %s, %s, label%d\n", r1, r2, go->u.label_no);
                break;
            case GR:
                fprintf(f, "  bgt %s, %s, label%d\n", r1, r2, go->u.label_no);
                break;
            case GE:
                fprintf(f, "  bge %s, %s, label%d\n", r1, r2, go->u.label_no);
                break;
            case NE:
                fprintf(f, "  bne %s, %s, label%d\n", r1, r2, go->u.label_no);
                break;
        }
    }
    else if(op1->kind==CONSTANT && op2->kind!=CONSTANT) {
        int reg2 = getReg(f, op2);
        char r2[20];
        memset(r2, 0, sizeof(r2));
        if(op2->kind==STAR) {
            fprintf(f, "  lw $s2, 0(%s)\n", names[reg2]);
            strcpy(r2, "$s2");
        }
        else {
            strcpy(r2, names[reg2]);
        }
        switch(rp) {
            case EQ:
                fprintf(f, "  beq %d, %s, label%d\n", op1->u.val, r2, go->u.label_no);
                break;
            case LS:
                fprintf(f, "  blt %d, %s, label%d\n", op1->u.val, r2, go->u.label_no);
                break;
            case LE:
                fprintf(f, "  ble %d, %s, label%d\n", op1->u.val, r2, go->u.label_no);
                break;
            case GR:
                fprintf(f, "  bgt %d, %s, label%d\n", op1->u.val, r2, go->u.label_no);
                break;
            case GE:
                fprintf(f, "  bge %d, %s, label%d\n", op1->u.val, r2, go->u.label_no);
                break;
            case NE:
                fprintf(f, "  bne %d, %s, label%d\n", op1->u.val, r2, go->u.label_no);
                break;
        }
    }
    else if(op1->kind!=CONSTANT && op2->kind==CONSTANT) {
        int reg1 = getReg(f, op1);
        char r1[20];
        memset(r1, 0, sizeof(r1));
        if(op1->kind==STAR) {
            fprintf(f, "  lw $s1, 0(%s)\n", names[reg1]);
            strcpy(r1, "$s1");
        }
        else {
            strcpy(r1, names[reg1]);
        }
        switch(rp) {
            case EQ:
                fprintf(f, "  beq %s, %d, label%d\n", r1, op2->u.val, go->u.label_no);
                break;
            case LS:
                fprintf(f, "  blt %s, %d, label%d\n", r1, op2->u.val, go->u.label_no);
                break;
            case LE:
                fprintf(f, "  ble %s, %d, label%d\n", r1, op2->u.val, go->u.label_no);
                break;
            case GR:
                fprintf(f, "  bgt %s, %d, label%d\n", r1, op2->u.val, go->u.label_no);
                break;
            case GE:
                fprintf(f, "  bge %s, %d, label%d\n", r1, op2->u.val, go->u.label_no);
                break;
            case NE:
                fprintf(f, "  bne %s, %d, label%d\n", r1, op2->u.val, go->u.label_no);
                break;
        }
    }
    for(int i=8; i<=15; i++) {
        regs[i].used = 0;
    }
}

void mipsGoto(FILE* f, InterCode ic)
{
    Operand op = ic->u.op;
    if(op->kind!=LABEL) {
        printf("goto type error:%d\n", op->kind);
        exit(1);
    }
    fprintf(f, "  j label%d\n", op->u.label_no);
}

void mipsLabel(FILE* f, InterCode ic)
{
    fprintf(f, "label%d:\n", ic->u.op->u.label_no);
}

void mipsCall(FILE* f, InterCode ic)
{
    Operand op1 = ic->u.assign.left;
    Operand op2 = ic->u.assign.right;
    argsNo = 0;
    paramNo = 0;
    fprintf(f, "  addi, $sp, $sp, -4\n");
    fprintf(f, "  sw $ra, 0($sp)\n");
    int reg1 = getReg(f, op1);
    fprintf(f, "  jal %s\n", op2->u.fname);
    fprintf(f, "  move %s, $v0\n", names[reg1]);
    clearReg(f, reg1);
    fprintf(f, "  lw $ra, 0($sp)\n");
	fprintf(f, "  addi $sp, $sp, 4\n");
}

void mipsRead(FILE* f, InterCode ic)
{
    fprintf(f, "  addi $sp, $sp, -4\n");
    fprintf(f, "  sw $ra, 0($sp)\n");
	fprintf(f, "  jal read\n");
    int reg1 = getReg(f, ic->u.op);
    if(ic->u.op->kind == STAR) {
        fprintf(f, "  sw $v0, 0(%s)\n", names[reg1]);
    }
    else {
        fprintf(f, "  move %s, $v0\n", names[reg1]);
    }
    clearReg(f, reg1);
	fprintf(f, "  lw $ra, 0($sp)\n");
	fprintf(f, "  addi $sp, $sp, 4\n");
}

void mipsWrite(FILE* f, InterCode ic)
{
    //printf("mips write\n");
    fprintf(f, "  addi $sp, $sp, -4\n");
    fprintf(f, "  sw $ra, 0($sp)\n");
    int reg1 = getReg(f, ic->u.op);
    if(ic->u.op->kind == STAR) {
        fprintf(f, "  lw $a0, 0(%s)\n", names[reg1]);
    }
    else {
        fprintf(f, "  move $a0, %s\n", names[reg1]);
    }
	fprintf(f, "  jal write\n");
    clearReg(f, reg1);
    fprintf(f, "  lw $ra, 0($sp)\n");
	fprintf(f, "  addi $sp, $sp, 4\n");
}

void mipsDec(FILE* f, InterCode ic)
{
    //一维数组
    int size = ic->u.dec.size;
    Operand op = ic->u.dec.op;
    //spOffset -= 4;
    Var v = (Var)malloc(sizeof(struct Var_));
    spOffset -= size;
    v->offset = spOffset;
    char tmp[32];
    memset(tmp, 0, sizeof(tmp));
    if(op->kind == VARIABLE) {
        sprintf(tmp, "v%d", op->u.var_no);
    }
    else if(op->kind == TEMP) {
        sprintf(tmp, "t%d", op->u.temp_no);
    }
    /*else {
        printf("dec array kind %d\n", op->kind);
        exit(1);
    }*/
    v->name = (char*)malloc(sizeof(char)*strlen(tmp)+1);
    strcpy(v->name, tmp);
    insertVar(v);
}

void mipsAddr(FILE* f, InterCode ic)
{
    //卧槽，lab3写错了
    Operand op1 = ic->u.binop.op1;
    Operand op2 = ic->u.binop.op2;
    //printf("here1\n");
    char tmp[32];
    memset(tmp, 0, sizeof(tmp));
    //printf("op2 kind%d\n", op2->kind);
    if(op2->kind == VARIABLE) {
        sprintf(tmp, "v%d", op2->u.var_no);
    }
    else if(op2->kind == TEMP) {
        sprintf(tmp, "t%d", op2->u.temp_no);
    }
    //printf("here2\n");
    int reg1 = getReg(f, op1);
    Var v = findVar1(tmp);
    //printf("here3\n");
    if(!v) {
        printf("addr v null\n");
        exit(1);
    }
    //printf("here4\n");
    fprintf(f, "  la %s, %d($fp)\n", names[reg1], v->offset);
    clearReg(f, reg1);
    //printf("here5\n");
}

void writeReadWrite(FILE* f)
{
    fputs(".data\n_prompt: .asciiz \"Enter an integer:\"\n_ret: .asciiz \"\\n\"\n.globl main\n.text\n", f);
    fputs("\nread:\n  li $v0, 4\n  la $a0, _prompt\n  syscall\n  li $v0, 5\n  syscall\n  jr $ra\n", f);
    fputs("\nwrite:\n  li $v0, 1\n  syscall\n  li $v0, 4\n  la $a0, _ret\n  syscall\n  move $v0, $0\n  jr $ra\n", f);
}

InterCodes nextBlock(InterCodes ic)
{
    InterCodes p = ic;
    while(p) {
        switch(p->code->kind) {
            case FUNCDEC:
            case GOTO:
            case LABELDEC:
                return p;
        }
        p = p->next;
    }
    return NULL;
}

void clearReg(FILE* f, int i) {
    regs[i].used = 0;
    fprintf(f, "  sw %s, %d($fp)\n", names[i], regs[i].var->offset);
    for(int i=8; i<=15; i++) {
        regs[i].used = 0;
    }
}
