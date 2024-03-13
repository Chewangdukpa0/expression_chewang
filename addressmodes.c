#include <stdio.h>
#include <string.h>

typedef enum {
    DATA,
    ADDRESS,
    OPCODE,
    REGISTER,
    DC
} Token_type;

typedef enum {
    IMPLIED,
    IMMEDIATE,
    REG_DIRECT,
    REG_INDIRECT,
    INDIRECT,
    INVALID
} AMODE;

typedef struct {
    Token_type type;
    char *name;
} Token;

typedef struct {
    Token m1;
    Token m2;
    Token m3;
    Token m4;
} Expression;

AMODE movCheck(Expression *e) {
    Token_type reg = REGISTER;
    Token_type add = ADDRESS;
    Token_type lit = DATA;
    if (e->m2.type == reg && e->m3.type == reg) {
        return REG_DIRECT;
    } else if (e->m2.type == reg && e->m3.type == add) {
        if (e->m3.name[1] == '%') {
            return REG_INDIRECT;
        } else {
            return INDIRECT;
        }
    } else if (e->m2.type == reg && e->m3.type == lit) {
        return IMMEDIATE;
    }
    return INVALID;
}

AMODE pushCheck(Expression *e) {
    Token_type reg = REGISTER;
    Token_type add = ADDRESS;
    if (e->m2.type == reg) {
        return REG_DIRECT;
    } else if (e->m2.type == add) {
        if (e->m2.name[1] == '%') {
            return REG_INDIRECT;
        } else {
            return INDIRECT;
        }
    }
    return INVALID;
}

AMODE addressMode(Expression *e) {
    Token_type op = OPCODE;
    if (strcmp(e->m1.name, "mov") == 0) {
        return movCheck(e);
    } else if (strcmp(e->m1.name, "push") == 0) {
        return pushCheck(e);
    } else if (strcmp(e->m1.name, "hlt") == 0 ||
               strcmp(e->m1.name, "ret") == 0 ||
               strcmp(e->m1.name, "jne") == 0 ||
               strcmp(e->m1.name, "jg") == 0 ||
               strcmp(e->m1.name, "jl") == 0 ||
               strcmp(e->m1.name, "clf") == 0 ||
               strcmp(e->m1.name, "syscall") == 0) {
        return IMPLIED;
    } else if (strcmp(e->m1.name, "pop") == 0 ||
               strcmp(e->m1.name, "add") == 0 ||
               strcmp(e->m1.name, "sub") == 0 ||
               strcmp(e->m1.name, "div") == 0 ||
               strcmp(e->m1.name, "mul") == 0 ||
               strcmp(e->m1.name, "mod") == 0 ||
               strcmp(e->m1.name, "cmp") == 0) {
        return REG_DIRECT;
    }
    return INVALID;
}

int main() {
    Token_type op = OPCODE;
    Token_type reg = REGISTER;
    Token_type add = ADDRESS;
    Token_type lit = DATA;
    Token_type dc = DC;
    Expression e;
    Token mo = {op, "push"};
    Token mt = {add, "&%a"};
    Token mth = {dc, NULL};
    Token mf = {dc, NULL};
    e.m1 = mo;
    e.m2 = mt;
    e.m3 = mth;
    e.m4 = mf;
    AMODE result = addressMode(&e);
    printf("Expression input:\n");
    printf("Token 1: %s\n", e.m1.name);
    printf("Token 2: %s\n", e.m2.name);
    printf("Token 3: %s\n", e.m3.name);
    printf("Token 4: %s\n", e.m4.name);
    printf("Enum: %d\n", result);

    return 0;
}

