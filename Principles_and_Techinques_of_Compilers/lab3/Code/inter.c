#include "inter.h"
extern InterCodes interlist;
extern InterCodes lastinter;
extern vNode vlist;
extern StructNode structlist;
extern ArgList arglist;

int vNum = 1;
int labelNum = 1;
int tNum = 1;
int structNum = 1;

void writeFile(char* filename) {
    if(!filename) {
        printf("filename empty\n");
        return;
    }
    FILE* f = fopen(filename, "w");
    if(!f) {
        printf("f null\n");
        return;
    }
    InterCodes p = interlist;
    while(p) {
        switch(p->code->kind) {
            case FUNCDEC:
                fputs("FUNCTION ", f);
                fputs(p->code->u.op->u.fname, f);
                fputs(" :\n", f);
                break;
            case PARAM:
                fputs("PARAM ", f);
                /*char tmp[32];
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp,"%d",p->code->u.op->u.var_no);
                fputs(tmp, f);*/
                writeOp(p->code->u.op, f);
                fputs("\n", f);
                break;
            case RETURN:
                fputs("RETURN ", f);
                writeOp(p->code->u.op, f);
                fputs("\n", f);
                break;
            case RELOP:
                fputs("IF ", f);
                writeOp(p->code->u.rlp.op1, f);
                fputs(" ", f);
                writeRelop(p->code->u.rlp.rp, f);
                writeOp(p->code->u.rlp.op2, f);
                fputs(" GOTO ", f);
                writeOp(p->code->u.rlp.go, f);
                fputs("\n", f);
                break;
            case GOTO:
                fputs("GOTO ", f);
                writeOp(p->code->u.op, f);
                fputs("\n", f);
                break;
            case LABELDEC:
                fputs("LABEL ", f);
                writeOp(p->code->u.op, f);
                fputs(" :\n", f);
                break;
            case ASSIGN:
                writeOp(p->code->u.assign.left, f);
                fputs(" := ", f);
                writeOp(p->code->u.assign.right, f);
                fputs("\n", f);
                break;
            case READ:
                fputs("READ ", f);
                writeOp(p->code->u.op, f);
                fputs(" \n", f);
                break;
            case CALL:
                writeOp(p->code->u.assign.left, f);
                fputs(" := CALL ", f);
                writeOp(p->code->u.assign.right, f);
                fputs(" \n", f);
                break;
            case WRITE:
                fputs("WRITE ", f);
                writeOp(p->code->u.op, f);
                fputs(" \n", f);
                break;
            case ARG:
                fputs("ARG ", f);
                writeOp(p->code->u.op, f);
                fputs(" \n", f);
                break;
            case DEC:
                fputs("DEC ", f);
                writeOp(p->code->u.dec.op, f);
                fputs(" ", f);
                char tmp[32];
	            memset(tmp, 0, sizeof(tmp));
                sprintf(tmp,"%d",p->code->u.dec.size);
                fputs(tmp, f);
                //fputs(p->code->u.dec.size, f);
                fputs(" \n", f);
                break;
            case ADDR:
                writeOp(p->code->u.binop.op1, f);
                fputs(" := &", f);
                writeOp(p->code->u.binop.op2, f);
                fputs(" \n", f);
                break;
            case ADD:
                writeOp(p->code->u.binop.result, f);
                fputs(" := ", f);
                writeOp(p->code->u.binop.op1, f);
                fputs(" + ", f);
                writeOp(p->code->u.binop.op2, f);
                fputs("\n", f);
                break;
            case SUB:
                writeOp(p->code->u.binop.result, f);
                fputs(" := ", f);
                writeOp(p->code->u.binop.op1, f);
                fputs(" - ", f);
                writeOp(p->code->u.binop.op2, f);
                fputs("\n", f);
                break;
            case MUL:
                writeOp(p->code->u.binop.result, f);
                fputs(" := ", f);
                writeOp(p->code->u.binop.op1, f);
                fputs(" * ", f);
                writeOp(p->code->u.binop.op2, f);
                fputs("\n", f);
                break;
            case DIV:
                writeOp(p->code->u.binop.result, f);
                fputs(" := ", f);
                writeOp(p->code->u.binop.op1, f);
                fputs(" / ", f);
                writeOp(p->code->u.binop.op2, f);
                fputs("\n", f);
                break;
        }
        p = p->next;
    }
}

void writeOp(Operand op, FILE* f) {
    char tmp[32];
	memset(tmp, 0, sizeof(tmp));
    switch(op->kind) {
        case VARIABLE:
            sprintf(tmp,"v%d",op->u.var_no);
            fputs(tmp, f);
            break;
        case LABEL:
            sprintf(tmp,"label%d",op->u.label_no);
            fputs(tmp, f);
            break;
        case CONSTANT:
            sprintf(tmp,"#%d",op->u.val);
            fputs(tmp, f);
            break;
        case TEMP:
            sprintf(tmp,"t%d",op->u.temp_no);
            fputs(tmp, f);
            break;
        case FUNC:
            fputs(op->u.fname, f);
            break;
        case STAR:
            fputs("*", f);
            writeOp(op->u.op, f);
            break;
    }
}

void writeRelop(Relop r, FILE* f) {
    switch(r) {
        case EQ:
            fputs("== ",f);
            break;
        case LS:
            fputs("< ",f);
            break;
        case LE:
            fputs("<= ",f);
            break;
        case GR:
            fputs("> ",f);
            break;
        case GE:
            fputs(">= ",f);
            break;
        case NE:
            fputs("!= ",f);
            break;
    }
}

int getSize(Type t) {
    if(t->kind == BASIC) { //int
        return 4;
    }
    else if(t->kind == ARRAY) {
        return t->u.array.size*getSize(t->u.array.elem); 
    }
    else if(t->kind == STRUCTURE) {
        int size = 0;
        FieldList f = t->u.structure;
        while(f) {
            size += getSize(f->type);
            f = f->next;
        }
        return size;
    }
}

bool paramStruct(char* s) {
    StructNode n = structlist;
    while(n) {
        if(strcmp(n->name, s)==0) {
            return true;
        }
        n = n->next;
    }
    return false;
}

Operand cVar(char* s, Type t) {
    //printf("create var: %s, type:%d\n", s, t->kind);
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = VARIABLE;
    op->u.var_no = vNum;
    op->name = (char*)malloc(sizeof(char)*strlen(s)+1);
    op->t = t;
    strcpy(op->name, s);
    vNode v = (vNode)malloc(sizeof(struct vNode_));
    v->name = (char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(v->name, s);
    //printf("inserted vnode name:%s\n", v->name);
    v->var_no = vNum;
    v->op = op;
    insertVNode(v);
    vNum++;
    return op;
}

Operand cConstant(int val) {
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = CONSTANT;
    op->u.val = val;
    return op;
}

Operand cLabel() {
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = LABEL;
    op->u.label_no = labelNum;
    labelNum++;
    return op;
}

Operand cTemp() {
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = TEMP;
    op->u.temp_no = tNum;
    tNum++;
    return op;
}

Operand cFunc(char* s) {
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = FUNC;
    op->u.fname = (char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(op->u.fname, s);
    return op;
}

Operand cStar(Operand op, Type t) {
    Operand op1 = (Operand)malloc(sizeof(struct Operand_));
    op1->kind = STAR;
    op1->u.op = op;
    op1->t = t;
    return op1;
}

void insertInterCode(InterCode ic) {
    if(!interlist) {
        interlist = (InterCodes)malloc(sizeof(struct InterCodes_));
        interlist->code = ic;
        interlist->next = NULL;
        lastinter = interlist;
    }
    else {
        InterCodes ics = (InterCodes)malloc(sizeof(struct InterCodes_));
        ics->code = ic;
        ics->next = NULL;
        lastinter->next = ics;
        lastinter = ics;
    }
}

void insertStructNode(StructNode s) {
    if(!structlist) {
        structlist = s;
    }
    else {
        s->next = structlist;
        structlist = s;
    }
}

void insertVNode(vNode v) {
    if(!vlist) {
        vlist = v;
    }
    else {
        v->next = vlist;
        vlist = v;
    }
}

void iFunDec(char* s) {
    Operand op = cFunc(s);
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = FUNCDEC;
    ic->u.op = op;
    insertInterCode(ic);
}

Operand iParam(char* s, Type t) {
    Operand op = cVar(s, t);
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = PARAM;
    ic->u.op = op;
    insertInterCode(ic);
    return op;
}

void iReturn(Operand op) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = RETURN;
    ic->u.op = op;
    insertInterCode(ic);
}

void iRelop(Operand op1, Operand op2, Relop relop, Operand go) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = RELOP;
    ic->u.rlp.op1 = op1;
    ic->u.rlp.op2 = op2;
    ic->u.rlp.go = go;
    ic->u.rlp.rp = relop;
    insertInterCode(ic);
}

void iGoto(Operand go) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = GOTO;
    ic->u.op = go;
    insertInterCode(ic);
}

void iLabel(Operand l) {
    //printf("insert label...\n");
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = LABELDEC;
    ic->u.op = l;
    insertInterCode(ic);
    //printf("insert label end\n");
}

void iAssign(Operand left, Operand right) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = ASSIGN;
    ic->u.assign.left = left;
    ic->u.assign.right = right;
    insertInterCode(ic);
}

void iCalculate(Operand t, Operand op1, Operand op2, int type) {
    //printf("icalculate\n");
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    switch(type) {
        case 1:
            ic->kind = ADD;
            break;
        case 2:
            ic->kind = SUB;
            break;
        case 3:
            ic->kind = MUL;
            break;
        case 4:
            ic->kind = DIV;
            break;
    }
    ic->u.binop.result = t;
    ic->u.binop.op1 = op1;
    ic->u.binop.op2 = op2;
    insertInterCode(ic);
    //printf("calculate end\n");
}

void iRead(Operand t) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = READ;
    ic->u.op = t;
    insertInterCode(ic);
}

void iCall(Operand t, Operand f) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = CALL;
    ic->u.assign.left = t;
    ic->u.assign.right = f;
    insertInterCode(ic);
}

void iWrite(Operand op) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = WRITE;
    ic->u.op = op;
    insertInterCode(ic);
}

void iArg(Operand arg) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = ARG;
    ic->u.op = arg;
    insertInterCode(ic);
}

void iDec(Operand op, int size) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = DEC;
    ic->u.dec.op = op;
    ic->u.dec.size = size;
    insertInterCode(ic);
}

void iAddr(Operand op1, Operand op2) {
    InterCode ic = (InterCode)malloc(sizeof(struct InterCode_));
    ic->kind = ADDR;
    ic->u.binop.op1 = op1;
    ic->u.binop.op2 = op2;
    insertInterCode(ic);
}

Operand findVar(char* s) {
    vNode v = vlist;
    //if(v==NULL) printf("vlist null\n");
    while(v) {
        if(strcmp(v->name, s)==0) {
            return v->op;
        }
        v = v->next;
    }
    return NULL;
}

myOffset getOffset(char* s, FieldList f) {
    //printf("get offset\n");
    int offset = 0;
    myOffset ret = (myOffset)malloc(sizeof(struct myOffset_));
    while(f) {
        //printf("current f:%s\n", f->name);
        if(strcmp(f->name, s)!=0) {
            offset += getSize(f->type);
            //printf("getsize end\n");
            f = f->next;
        }
        else {
            ret->offset = offset;
            ret->t = f->type;
            return ret;
        }
    }
    //printf("field error\n");
    exit(1);
    return NULL;
}

void translate(node* root) { //Program->ExtDefList
    if(!root) return;
    transExtDefList(root->child);
}

void transExtDefList(node* n) {
    if(n->child) { //ExtDefList->ExtDef ExtDefList
        transExtDef(n->child);
        transExtDefList(n->child->sibling);
    }
    //ExtDefList->null
}

void transExtDef(node* n) {
    if(strcmp(n->child->sibling->name, "ExtDecList")==0) { //ExtDef->Specifier ExtDecList SEMI
        ; //没有全局变量
    }
    else if(strcmp(n->child->sibling->name, "SEMI")==0) { //ExtDef->Specifier SEMI
        transSpecifier(n->child);
    }
    else { //ExtDef->Specifier FunDec Compst
        transSpecifier(n->child);
        transFunDec(n->child->sibling);
        transCompSt(n->child->sibling->sibling);
    }
}

Type transSpecifier(node* n) {
    //printf("specifier\n");
    if(strcmp(n->child->name, "TYPE")==0) { //Specifier->TYPE
        Type t = (Type)malloc(sizeof(struct Type_));
		t->kind = BASIC;
		if(strcmp(n->child->val,"int")==0){
			t->u.basic=INT;
		}
		else t->u.basic=FLOAT;
        return t;
    }
    else { //Specifier->StructSpecifier
        return transStructSpecifier(n->child);
    }
}

Type transStructSpecifier(node* n) {
    if(strcmp(n->child->sibling->name, "Tag")==0) { //StructSpecifier->STRUCT Tag, use struct
        //printf("use struct %s\n", n->child->sibling->child->val);
        HashNode h = find(n->child->sibling->child->val);
        if(!h) {
            printf("struct error1\n");
            exit(1);
        }
        return h->type;
    }
    else{ //StructSpecifier->STRUCT OptTag LC DefList RC
        if(n->child->sibling->child) { //OptTag not null
            //printf("def struct %s\n", n->child->sibling->child->val);
            HashNode h = find(n->child->sibling->child->val);
            if(!h) {
                printf("struct error2\n");
                exit(1);
            }
            return h->type;
        }
        else { // 没名字的
            //printf("no name struct\n");
            Type t  =(Type)malloc(sizeof(struct Type_));
            t->kind =  STRUCTURE;
            t->u.structure = DefList(n->child->sibling->sibling->sibling, true);
            return t;
        }
    }
}

Operand transVarDec(node* n, Type t, bool isParam, int arrayNum) {
    //printf("vardec ");
    if(!n->child->sibling) { //VarDec->ID
        //printf("id:%s\n", n->child->val);
        if(isParam) {
            //printf("param\n");
            //printf("param: %s\n", n->child->val);
            iParam(n->child->val, t);
            if(t->kind == STRUCTURE) { //param无array
                StructNode s = (StructNode)malloc(sizeof(struct StructNode_));
                s->name = (char*)malloc(sizeof(char)*strlen(n->child->val)+1);
                strcpy(s->name, n->child->val);
                insertStructNode(s);
            }
            return NULL;
        }
        else {
            //HashNode h = find(n->child->val);
            Operand op = cVar(n->child->val, t);
            if(t->kind == STRUCTURE && arrayNum==0) { //dec size
                int size = getSize(t);
                //printf("dec %d\n",size);
                iDec(op, size);
            }
            else if(arrayNum) {
                int size = getSize(t);
                iDec(op, size*arrayNum);
            }
            return op;
        }
    }
    else { //VarDec->VarDec LB INT RB, 只有一维且不是param
        if(isParam || strcmp(n->child->child->name, "ID")!=0) {
            //printf("array error\n");
            exit(1);
        }
        else {
            return transVarDec(n->child, t, isParam, atoi(n->child->sibling->sibling->val));
        }
    }
}

void transFunDec(node* n) {
    if(strcmp(n->child->sibling->sibling->name,"VarList")==0){//FunDec->ID LP VarList RP
        iFunDec(n->child->val);
        transVarList(n->child->sibling->sibling);
    }
    else { //FunDec->ID LP RP
        iFunDec(n->child->val);
    }
}

void transVarList(node* n) {
    if(n->child->sibling) { //VarList->ParamDec COMMA VarList
        transParamDec(n->child);
        transVarList(n->child->sibling->sibling);
    }
    else { //VarList->ParamDec
        transParamDec(n->child);
    }
}

void transParamDec(node* n) { //ParamDec->Specifier VarDec
    Type t = Specifier(n->child);
    transVarDec(n->child->sibling, t, true, 0);
}

void transCompSt(node* n) { //CompSt->LC DefList StmtList RC
    transDefList(n->child->sibling);
    transStmtList(n->child->sibling->sibling);
}

void transStmtList(node* n) {
    //printf("stmtlist\n");
    if(n->child) {  //StmtList->Stmt StmtList
        transStmt(n->child);
        transStmtList(n->child->sibling);
    }
    //StmtList->null
}

void transStmt(node* n) {
    //printf("stmt");
    if(strcmp(n->child->name, "Exp")==0) { //Stmt->Exp SEMI
        //printf("->exp\n");
        transExp(n->child);
    }
    else if(strcmp(n->child->name, "CompSt")==0) { //Stmt->CompSt
       // printf("->compst\n");
        transCompSt(n->child);
    }
    else if(strcmp(n->child->name, "RETURN")==0) { //Stmt->RETURN Exp SEMI
        //printf("->return\n");
        Operand op = transExp(n->child->sibling);
        iReturn(op);
    }
    else if(strcmp(n->child->name, "IF")==0) { //Exp->IF LP Exp RP Stmt (ELSE Stmt)
        //printf("->if...\n");
        if(!n->child->sibling->sibling->sibling->sibling->sibling) { //Exp->IF LP Exp RP Stmt
            Operand label1 = cLabel();
            Operand label2 = cLabel();
            transCond(n->child->sibling->sibling, label1, label2);
            iLabel(label1);
            transStmt(n->child->sibling->sibling->sibling->sibling);
            iLabel(label2);
        }
        else { //Exp->IF LP Exp RP Stmt ELSE Stmt
            Operand label1 = cLabel();
            Operand label2 = cLabel();
            Operand label3 = cLabel();
            node* tmp = n->child->sibling->sibling;
            transCond(tmp, label1, label2);
            iLabel(label1);
            tmp = tmp->sibling->sibling;
            transStmt(tmp);
            iGoto(label3);
            iLabel(label2);
            tmp = tmp->sibling->sibling;
            transStmt(tmp);
            iLabel(label3);
        }
    }
    else if(strcmp(n->child->name, "WHILE")==0) { //Exp->WHILE LP Exp RP Stmt
        //printf("->while ...\n");
        Operand label1 = cLabel();
        Operand label2 = cLabel();
        Operand label3 = cLabel();
        iLabel(label1);
        node* tmp = n->child->sibling->sibling;
        transCond(tmp, label2, label3);
        iLabel(label2);
        transStmt(tmp->sibling->sibling);
        iGoto(label1);
        iLabel(label3);
    }
}

void transDefList(node* n) {
    //printf("def list\n");
    if(n->child) { //DefList->Def DefList
        transDef(n->child);
        transDefList(n->child->sibling);
    }
    //DefList->null
}

void transDef(node* n) { //Def->Specifier DecList SEMI
    //printf("def\n");
    Type t = transSpecifier(n->child);
    transDecList(n->child->sibling, t);
}

void transDecList(node* n, Type t) {
    //printf("declist\n");
    transDec(n->child, t); //DecList->Dec
    if(n->child->sibling) { //DecList->Dec COMMA DecList
        transDecList(n->child->sibling->sibling, t);
    }
}

void transDec(node* n, Type t) {
    //printf("dec\n");
    if(!n->child->sibling) { //Dec->VarDec
        transVarDec(n->child, t, false, 0);
    }
    else { //Dec->VarDec ASSIGN Exp
        //printf("dec->vardec assign exp\n");
        Operand op1 = transVarDec(n->child, t, false, 0);
        Operand op2 = transExp(n->child->sibling->sibling);
        iAssign(op1, op2);
    }
}

Operand transExp(node* n) {
    //printf("exp");
    if(strcmp(n->child->name,"Exp")==0){
        if(strcmp(n->child->sibling->name, "ASSIGNOP")==0){//Exp->Exp ASSIGNOP Exp
            //printf("->exp assignop exp\n");
            Operand op1 = transExp(n->child);
            Operand op2 = transExp(n->child->sibling->sibling);
            iAssign(op1, op2);
            return op1;
        }
        else if(strcmp(n->child->sibling->name, "AND")==0 || strcmp(n->child->sibling->name, "OR")==0 || strcmp(n->child->sibling->name, "RELOP")==0) {
            //Exp->Exp AND/RELOP/OR Exp
            //printf("->exp relop exp\n");
            Operand label1 = cLabel();
            Operand label2 = cLabel();
            Operand t1 = cTemp();
            Operand zero = cConstant(0);
            Operand one = cConstant(1);
            iAssign(t1, zero);
            transCond(n, label1, label2);
            iLabel(label1);
            iAssign(t1, one);
            iLabel(label2);
            return t1;
        }
        else if(strcmp(n->child->sibling->name, "PLUS")==0) { //Exp->Exp PLUS Exp
            //printf("->exp+exp\n");
            Operand op1 = transExp(n->child);
            Operand op2 = transExp(n->child->sibling->sibling);
            Operand t1 = cTemp();
            iCalculate(t1, op1, op2, 1);
            return t1;
        }
        else if(strcmp(n->child->sibling->name, "MINUS")==0) { //Exp->Exp MINUS Exp
            //printf("->exp-exp\n");
            Operand op1 = transExp(n->child);
            Operand op2 = transExp(n->child->sibling->sibling);
            Operand t1 = cTemp();
            iCalculate(t1, op1, op2, 2);
            return t1;
        }
        else if(strcmp(n->child->sibling->name, "STAR")==0) { //Exp->Exp STAR Exp
            //printf("->exp*exp\n");
            Operand op1 = transExp(n->child);
            Operand op2 = transExp(n->child->sibling->sibling);
            Operand t1 = cTemp();
            iCalculate(t1, op1, op2, 3);
            return t1;
        }
        else if(strcmp(n->child->sibling->name, "DIV")==0) { //Exp->Exp DIV Exp
            //printf("->exp/exp\n");
            Operand op1 = transExp(n->child);
            Operand op2 = transExp(n->child->sibling->sibling);
            Operand t1 = cTemp();
            iCalculate(t1, op1, op2, 4);
            return t1;
        }
        else if(strcmp(n->child->sibling->name, "LB")==0) { //Exp->Exp LB Exp RB, 一维array
            //printf("->array\n");
            Operand op1 = transExp(n->child);
            //printf("trans op1 end\n");
            //printf("array op1 kind:%d\n", op1->t->kind);
            Operand op2 = transExp(n->child->sibling->sibling);
            //printf("trans op2 end\n");
            if(op1->kind == VARIABLE) {
                int size = getSize(op1->t);
                //printf("op1 var: t%d\n", tNum);
                Operand t1 = cTemp();
                iAddr(t1, op1);
                if(op2->kind == CONSTANT) {
                    //printf("op2 constant: t%d\n", tNum);
                    Operand t2 = cTemp();
                    iCalculate(t2, t1, cConstant(size*op2->u.val), 1);
                    return cStar(t2, op1->t);
                }
                else {
                    //printf("op2 not constant: t%d\n", tNum);
                    Operand t2 = cTemp();
                    iCalculate(t2, op2, cConstant(size), 3);
                    Operand t3 = cTemp();
                    iCalculate(t3, t1, t2, 1);
                    return cStar(t3, op1->t);
                }
            }
            else { //star
                //printf("op1 star\n");
                int size = getSize(op1->t->u.array.elem);
                if(op2->kind == CONSTANT) {
                    //printf("op2 constant\n");
                    Operand t2 = cTemp();
                    iCalculate(t2, op1, cConstant(size*op2->u.val), 1);
                    //printf("array end\n");
                    //return cStar(t2, op1->t->u.array.elem);
                    return cStar(t2, op1->t->u.array.elem);
                }
                else {
                    //printf("op2 not constant: t%d\n", tNum);
                    Operand t2 = cTemp();
                    iCalculate(t2, op2, cConstant(size), 3);
                    //printf("op2 not constant2: t%d\n", tNum);
                    Operand t3 = cTemp();
                    iCalculate(t3, op1, t2, 1);
                    //return cStar(t3, op1->t->u.array.elem);
                    return cStar(t3, op1->t->u.array.elem);
                }

            }
        }
        else if(strcmp(n->child->sibling->name, "DOT")==0) { //Exp->Exp DOT ID, struct
            //printf("->exp dot exp\n");
            Operand op1 = transExp(n->child);
            //printf("dot op1 end\n");
            /*if(n->child->sibling->sibling->val) printf("id:%s\n", n->child->sibling->sibling->val);
            else {
                //printf("id null\n");
                exit(1);
            }
            printf("struct op1 type:%d\n", op1->t->kind);*/
            //myOffset offsetInfo = getOffset(n->child->sibling->sibling->val, op1->t->u.structure);
            myOffset offsetInfo;
            if(op1->t->kind == STRUCTURE) {
                //printf("st op1 kind structure\n");
                offsetInfo = getOffset(n->child->sibling->sibling->val, op1->t->u.structure); //嵌套struct...
            }
            else if(op1->t->kind == ARRAY) { //array里给star插type插错了，无语...
                //printf("st op1 kind array\n");
                offsetInfo = getOffset(n->child->sibling->sibling->val, op1->t->u.array.elem->u.structure);
            }
            //printf("get offset end\n");
            int offset = offsetInfo->offset;
            Type t = offsetInfo->t;
            //printf("offset:%d\n",offset);
            if(op1->kind == VARIABLE){
                //printf("var\n");
                if(paramStruct(op1->name)) {
                    if(offset!=0){
                        Operand t1 = cTemp();
                        iCalculate(t1, op1, cConstant(offset), 1);
                        //printf("exp dot id end\n");
                        return cStar(t1, t);
                    }
                    else {
                        //printf("exp dot id end\n");
                        return cStar(op1, t);
                    }
                }
                else {
                    //printf("not param struct\n");
                    Operand t1 = cTemp();
                    //printf("t1 = &op1\n");
                    iAddr(t1, op1);
                    //printf("t2 = t1 + %d\n", offset);
                    if(offset!=0){
                        Operand t2 = cTemp();
                        iCalculate(t2, t1, cConstant(offset), 1);
                        //printf("exp dot id end\n");
                        return cStar(t2, t);
                    }
                    else {
                        //printf("exp dot id end\n");
                        return cStar(t1, t);
                    }
                }
            }
            else if(op1->kind == STAR) { //star, struct数组.xxx，坑...
                //printf("star\n");
                /*if(!op1->u.op) {
                    printf("op1 error\n");
                    exit(1);
                }*/
                Operand op = op1->u.op;
                //printf("here\n");
                if(offset!=0) { //已经是*tx了， 取tx再加offset...
                    Operand t1 = cTemp();
                    iCalculate(t1, op, cConstant(offset), 1);
                    //iCalculate(t1, op1, cConstant(offset), 1);
                    //printf("exp dot id end\n");
                    return cStar(t1, t);
                }
                else {
                    //printf("exp dot id end\n");
                    return op1;
                }
            }
            /*else {
                printf("struct error, op1 kind:%d!!!\n", op1->kind);
                exit(1);
            }*/
        }
    }
    else if(strcmp(n->child->name, "LP")==0) { //Exp->LP Exp RP
        //printf("->(exp)\n");
        return transExp(n->child->sibling);
    }
    else if(strcmp(n->child->name, "MINUS")==0) { //Exp->MINUS Exp
        //printf("->-exp\n");
        Operand t1 = cTemp();
        Operand op1 = transExp(n->child->sibling);
        Operand zero = cConstant(0);
        iCalculate(t1, zero, op1, 2);
        return t1;
    }
    else if(strcmp(n->child->name, "NOT")==0) { //Exp->NOT Exp
        Operand label1 = cLabel();
        Operand label2 = cLabel();
        Operand t1 = cTemp();
        Operand zero = cConstant(0);
        Operand one = cConstant(1);
        iAssign(t1, zero);
        transCond(n, label1, label2);
        iLabel(label1);
        iAssign(t1, one);
        iLabel(label2);
        return t1;
    }
    else if(strcmp(n->child->name,"ID")==0) {
        if(!n->child->sibling) { //Exp->ID
            //printf("->id:%s\n", n->child->val);
            Operand op = findVar(n->child->val);
            if(!op) {
                //printf("error!!!\n");
                exit(1);
            }
            return op;
        }
        else if(strcmp(n->child->sibling->sibling->name, "Args")==0) { //Exp->ID LB Args RB
            //ArgList arglist = transArgs(n->child->sibling->sibling);
            arglist = NULL;
            transArgs(n->child->sibling->sibling);
            if(strcmp(n->child->val, "write")==0) {
                iWrite(arglist->op);
                return NULL;
            }
            else {
                Operand t1 = cTemp();
                while(arglist) {
                    iArg(arglist->op);
                    arglist = arglist->next;
                }
                Operand f = cFunc(n->child->val);
                iCall(t1, f);
                return t1;
            }
        }
        else { //Exp->ID LB RB
            Operand t1 = cTemp();
            if(strcmp(n->child->val, "read")==0) {
                //printf("read\n");
                iRead(t1);
            }
            else {
                //printf("call\n");
                Operand f = cFunc(n->child->val);
                iCall(t1, f);
            }
            return t1;
        }
    }
    else if(strcmp(n->child->name,"INT")==0) { //Exp->INT
        //printf("->int\n");
        return cConstant(atoi(n->child->val));
    }
    else if(strcmp(n->child->name,"FLOAT")==0) { //Exp->FLOAT, 没有
        ;
    }
}

void transCond(node* n, Operand labelT, Operand labelF) {
    //printf("trans cond\n");
    if(strcmp(n->child->name, "NOT")==0) { //Exp->NOT Exp
        return transCond(n->child->sibling, labelF, labelT);
    }
    else if(strcmp(n->child->name, "Exp")==0) {
        if(strcmp(n->child->sibling->name, "RELOP")==0) { //Exp->Exp RELOP Exp
            Operand t1 = transExp(n->child);
            Operand t2 = transExp(n->child->sibling->sibling);
            Relop r = getRelop(n->child->sibling);
            iRelop(t1, t2, r, labelT);
            iGoto(labelF);
        }
        else if(strcmp(n->child->sibling->name, "AND")==0) { //Exp->Exp AND Exp
            Operand label1 = cLabel();
            transCond(n->child, label1, labelF);
            iLabel(label1);
            transCond(n->child->sibling->sibling, labelT, labelF);
        }
        else if(strcmp(n->child->sibling->name, "OR")==0) { //Exp->Exp OR Exp
            Operand label1 = cLabel();
            transCond(n->child, labelT, label1);
            iLabel(label1);
            transCond(n->child->sibling->sibling, labelT, labelF);
        }
    }
    else { //if Exp
        Operand t1 = transExp(n);
        Operand t2 = cConstant(0);
        iRelop(t1, t2, NE, labelT);
        iGoto(labelF);
    }
    //printf("trans cond end\n");
}

/*ArgList transArgs(node* n) {
    ArgList arglist = (ArgList)malloc(sizeof(struct ArgList_));
    if(!n->child->sibling) { //Args->Exp
        arglist->op = transExp(n->child);
    }
    else { //Args->Exp COMMA Args 无语，要反着插
        //arglist->op = transExp(n->child);
        //arglist->next = transArgs(n->child->sibling->sibling);
    }
    return arglist;
}*/

void insertArg(ArgList arg) {
    if(!arglist) {
        arglist = arg;
    }
    else {
        arg->next = arglist;
        arglist = arg;
    } 
}

void transArgs(node* n) {
    ArgList arg = (ArgList)malloc(sizeof(struct ArgList_));

    arg->op = transExp(n->child);
    insertArg(arg);
    if(n->child->sibling) { //Args->Exp COMMA Args
        transArgs(n->child->sibling->sibling);
    }
}

Relop getRelop(node* n) {
    if(strcmp(n->val, "==")==0) {
        return EQ;
    }
    else if(strcmp(n->val, "<")==0) {
        return LS;
    }
    else if(strcmp(n->val, "<=")==0) {
        return LE;
    }
    else if(strcmp(n->val, ">")==0) {
        return GR;
    }
    else if(strcmp(n->val, ">=")==0) {
        return GE;
    }
    else if(strcmp(n->val, "!=")==0) {
        return NE;
    }
    else {
        printf("get relop error\n");
        exit(1);
    }
}