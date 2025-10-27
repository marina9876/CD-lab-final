#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1, ip = 0;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }

void show(char* action) {
    // Print stack without the extra $
    for(int i=0; i<=top; i++) printf("%c", stack[i]);
    printf("\t\t%s\t\t%s\n", input+ip, action);
}

int main() {
    printf("Enter expression (use a,b as operands): ");
    scanf("%s", input);
    
    strcat(input, "$");  // Add end marker
    
    push('$');
    printf("\nStack\t\tInput\t\tAction\n");
    show("--");
    
    while(1) {
        // ACCEPT if stack has $E and input has $
        if(stack[top]=='E' && stack[top-1]=='$' && input[ip]=='$') {
            show("ACCEPT"); 
            break;
        }
        
        // REDUCE if possible
        int reduced = 0;
        
        // Rule 1: E -> a or E -> b
        if(stack[top]=='a' || stack[top]=='b') {
            show(stack[top]=='a' ? "E->a" : "E->b");
            pop(); push('E');
            reduced = 1;
        }
        // Rule 2: E -> E+E
        else if(top>=2 && stack[top-2]=='E' && stack[top-1]=='+' && stack[top]=='E') {
            show("E->E+E");
            pop(); pop(); pop(); push('E');
            reduced = 1;
        }
        // Rule 3: E -> E-E
        else if(top>=2 && stack[top-2]=='E' && stack[top-1]=='-' && stack[top]=='E') {
            show("E->E-E");
            pop(); pop(); pop(); push('E');
            reduced = 1;
        }
        // Rule 4: E -> E*E  
        else if(top>=2 && stack[top-2]=='E' && stack[top-1]=='*' && stack[top]=='E') {
            show("E->E*E");
            pop(); pop(); pop(); push('E');
            reduced = 1;
        }
        // Rule 5: E -> E/E
        else if(top>=2 && stack[top-2]=='E' && stack[top-1]=='/' && stack[top]=='E') {
            show("E->E/E");
            pop(); pop(); pop(); push('E');
            reduced = 1;
        }
        
        if(reduced) continue;
        
        // SHIFT if we have input left
        if(input[ip] != '$') {
            char temp[20];
            sprintf(temp, "shift %c", input[ip]);
            push(input[ip++]);
            show(temp);
        }
        // REJECT if no reduction possible and no input left
        else {
            show("REJECT"); 
            break;
        }
    }
    return 0;
}