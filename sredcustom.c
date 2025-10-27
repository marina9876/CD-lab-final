#include <stdio.h>
#include <string.h>

char stack[50];
int top = -1;

struct Rule {
    char rhs[10];
    char lhs;
};

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';  
}

void pop(int n) {
    for(int i = 0; i < n; i++) {
        top--;
    }
    stack[top + 1] = '\0';
}

int reduce(struct Rule rules[], int count) {
    for (int i = 0; i < count; i++) {
        int len = strlen(rules[i].rhs);
        if (top >= len - 1) {  // Fixed condition
            // Check if top 'len' elements match the rule
            int match = 1;
            for(int j = 0; j < len; j++) {
                if(stack[top - len + 1 + j] != rules[i].rhs[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("REDUCE %s → %c\n", rules[i].rhs, rules[i].lhs);
                pop(len);
                push(rules[i].lhs);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char input[20];
    int i = 0;
    printf("Enter the expression: ");
    scanf("%s", input);

    // Define grammar rules (order matters for precedence!)
    struct Rule rules[] = {
        {"(E)", 'E'},  // Parentheses highest
        {"E*E", 'E'},  // Multiplication 
        {"E+E", 'E'},  // Addition
        {"i", 'E'}     // Identifiers
    };
    int count = sizeof(rules) / sizeof(rules[0]);

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    
    // Add end marker
    strcat(input, "$");
    push('$');
    
    char a = input[i];
    while (a != '\0') {
        printf("%-15s\t%-10s\t", stack, input + i);
        
        // Try reduction first
        if (reduce(rules, count)) {
            printf("(reduced)\n");
            continue;
        }
        
        // Then shift
        if(a != '$') {
            printf("SHIFT %c\n", a);
            push(a);
            a = input[++i];
        } else {
            // Acceptance check
            if (top == 1 && stack[0] == '$' && stack[1] == 'E' && input[i] == '$') {
                printf("ACCEPT\n");
                break;
            } else {
                printf("REJECT\n");
                break;
            }
        }
    }

    return 0;
}