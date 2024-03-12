#include <stdio.h>
#include <string.h>
#include <ctype.h> 

enum types {
    ADDRESS,
    REGISTER,
    OPCODE,
    LITREAL
};

struct instruction{
    enum types type;
    char value[100];
};

enum types match_types(const char *str, struct instruction *i1) {
    if ((strcmp(str, "mov") == 0) || (strcmp(str, "ADD") == 0)) {
        strcpy(i1->value, str);
        return OPCODE;
    } else if (str[0] == '%') {
	printf("%c\n",str[0]);
        strcpy(i1->value, str);
        return REGISTER;
    } else if (str[0] == '[') {
            strcpy(i1->value, str);
            return ADDRESS;
    } else if(isdigit(str[0])){
            strcpy(i1->value, str);
            return LITREAL;

    }
}

int main() {
    struct instruction i1;
    const char *check = "[20]";
    enum types ans = match_types(check, &i1);
    i1.type = ans;
    printf("Type: %d\n", i1.type);
    printf("Value: %s\n", i1.value);
    return 0;
}
