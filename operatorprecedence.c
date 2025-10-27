#include <stdio.h>
#include <string.h>
#include <ctype.h>

char q[9][9] = {
    {'>', '>', '<', '<', '<', '<', '>', '<', '>'},
    {'>', '>', '<', '<', '<', '<', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '<', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '<', '>', '<', '>'},
    {'>', '>', '<', '<', '<', '<', '>', '<', '>'},
    {'<', '<', '<', '<', '<', '<', '=', '<', 'E'},
    {'>', '>', '>', '>', '>', 'E', '>', 'E', '>'},
    {'>', '>', '>', '>', '>', 'E', '>', 'E', '>'},
    {'<', '<', '<', '<', '<', '<', 'E', '<', 'A'}
};

char st[30], qs[30];
int top = -1, r = -1, p = 0;

void push(char a) {
    st[++top] = a;
}

char pop() {
    return st[top--];
}

int find(char a) {
    switch (a) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case '(': return 5;
        case ')': return 6;
        case 'a': return 7;
        case '$': return 8;
        default: return -1;
    }
}

void displayShift(char a) {
    printf("\nShift %c", a);
}

void displayReduce(char a) {
    if (isalpha(a))
        printf("\nReduce E -> %c", a);
    else if (strchr("+-*/^", a))
        printf("\nReduce E -> E%cE", a);
    else if (a == ')')
        printf("\nReduce E -> (E)");
}

int rel(char a, char b, char d) {
    if (isalpha(a)) a = 'a';
    if (isalpha(b)) b = 'a';
    return q[find(a)][find(b)] == d;
}

int main() {
    char s[100];
    printf("\nOperator Precedence Parser\n");
    printf("\nEnter the arithmetic expression ending with $: ");
    fgets(s, sizeof(s), stdin);

    // Remove newline if present
    s[strcspn(s, "\n")] = 0;

    push('$');

    while (1) {
        if (s[p] == '$' && st[top] == '$') {
            printf("\n\nAccepted");
            break;
        } else if (rel(st[top], s[p], '<') || rel(st[top], s[p], '=')) {
            displayShift(s[p]);
            push(s[p]);
            p++;
        } else if (rel(st[top], s[p], '>')) {
            do {
                r++;
                qs[r] = pop();
                displayReduce(qs[r]);
            } while (!rel(st[top], qs[r], '<'));
        } else {
            printf("\n\nError in parsing!");
            break;
        }
    }

    return 0;
}
