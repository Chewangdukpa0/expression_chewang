#include <stdio.h>
#include <stdlib.h> 

typedef enum {
    DATA,
    ADDRESS,
    OPCODE,
    REGISTER,
    DC
} Token_type;

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

void addExpress(Token *Token_c, int toklen, Expression *expressions, int num_exp) {
    Token_type x = OPCODE;
    int count = -1, i = 0;

    while (i < toklen) {
        if (Token_c[i].type == x) {
            count++;
            expressions[count].m1 = Token_c[i];
            expressions[count].m2.type = expressions[count].m3.type = expressions[count].m4.type = DC;
            expressions[count].m2.name = expressions[count].m3.name = expressions[count].m4.name = NULL;
        } else {
            if (expressions[count].m2.type == DC) {
                expressions[count].m2 = Token_c[i];
            } else if (expressions[count].m3.type == DC) {
                expressions[count].m3 = Token_c[i];
            } else if (expressions[count].m4.type == DC) {
                expressions[count].m4 = Token_c[i];
            }
        }
        i++;
    }
}



int main() {
    // Example token array
    Token Token_c[] = {
        {OPCODE, "mov"},
        {REGISTER, "a"},
        {DATA, "12"},
        //{DATA,"14"},

        {OPCODE, "add"},
        //{DATA, "13"},
        {DATA, "14"},
        {DATA, "16"},
    
        {OPCODE, "mov"},
        {REGISTER, "b"},
        {DATA, "17"},
        {DATA, "29"},
        //{DATA, "90"},

        {OPCODE, "mov"},
        {REGISTER, "b"},
        {DATA, "99"},
        {DATA, "90"}

	//{DATA,"19"}
    };
	
	int num_exp=0;

   	int num_tokens = sizeof(Token_c) / sizeof(Token_c[0]);
	printf("%d is number of tokens \n",num_tokens);

	//number of opcodes to create exp array
printf("no of tokens :%d \n",num_tokens);
	for(int i=0;i<num_tokens;i++)
        {
                if(Token_c[i].type==OPCODE)
                        num_exp++;
        }
	
	printf("num of opcodes %d\n",num_exp);
	Expression expressions[num_exp];


    	addExpress(Token_c, num_tokens, expressions, num_exp);
        printf("Expression %d: %s \n", 1, expressions[3].m4.name);
	    for (int i = 0; i < num_exp; i++) {
       			 printf("Expression %d: %s %s %s %s\n", i + 1, expressions[i].m1.name, expressions[i].m2.name,
              		 expressions[i].m3.name,expressions[i].m4.name );
    	}

    return 0;
}
