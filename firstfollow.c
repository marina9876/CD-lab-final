#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prod[20][20];
char firsts[26][20];
char follows[26][20];
int doneFirst[26], doneFollow[26];

int isTerminal(char c) {
    return !isupper(c);
}

int contains(char *s, char c) {
    for (int i = 0; s[i]; i++)
        if (s[i] == c)
            return 1;
    return 0;
}

void add(char *s, char c) {
    if (!contains(s, c)) {
        int l = strlen(s);
        s[l] = c;
        s[l + 1] = '\0';
    }
}

void findFirst(char X) {
    char result[20] = "";
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == X) {
            for (int j = 2; prod[i][j]; j++) {
                char ch = prod[i][j];
                if (isTerminal(ch)) {     // Case 1: Terminal
                    add(result, ch);
                    break;
                } else {                   // Case 2: Non-terminal
                    if (!doneFirst[ch - 'A'])
                        findFirst(ch);
                    for (int k = 0; firsts[ch - 'A'][k]; k++) {
                        if (firsts[ch - 'A'][k] != 'e')
                            add(result, firsts[ch - 'A'][k]);
                        else if (prod[i][j + 1] == '\0')
                            add(result, 'e');
                    }
                    if (!contains(firsts[ch - 'A'], 'e'))
                        break; // stop if epsilon not in FIRST
                }
            }
        }
    }
    strcpy(firsts[X - 'A'], result);
    doneFirst[X - 'A'] = 1;
}

void findFollow(char X) {
    char result[20] = "";
    if (X == prod[0][0])
        add(result, '$'); // add $ for start symbol

    for (int i = 0; i < n; i++) {
        for (int j = 2; prod[i][j]; j++) {
            if (prod[i][j] == X) {
                char next = prod[i][j + 1];
                if (next == '\0') { // at end
                    if (prod[i][0] != X) {
                        if (!doneFollow[prod[i][0] - 'A'])
                            findFollow(prod[i][0]);
                        for (int k = 0; follows[prod[i][0] - 'A'][k]; k++)
                            add(result, follows[prod[i][0] - 'A'][k]);
                    }
                } else if (isTerminal(next)) {
                    add(result, next);
                } else {
                    for (int k = 0; firsts[next - 'A'][k]; k++) {
                        if (firsts[next - 'A'][k] != 'e')
                            add(result, firsts[next - 'A'][k]);
                    }
                    if (contains(firsts[next - 'A'], 'e')) {
                        if (!doneFollow[prod[i][0] - 'A'])
                            findFollow(prod[i][0]);
                        for (int k = 0; follows[prod[i][0] - 'A'][k]; k++)
                            add(result, follows[prod[i][0] - 'A'][k]);
                    }
                }
            }
        }
    }
    strcpy(follows[X - 'A'], result);
    doneFollow[X - 'A'] = 1;
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (like E=E+T or T=i):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    // Compute FIRST sets
    for (int i = 0; i < n; i++)
        if (!doneFirst[prod[i][0] - 'A'])
            findFirst(prod[i][0]);

    // Compute FOLLOW sets
    for (int i = 0; i < n; i++)
        if (!doneFollow[prod[i][0] - 'A'])
            findFollow(prod[i][0]);

    printf("\nFIRST sets:\n");
    for (int i = 0; i < 26; i++)
        if (doneFirst[i])
            printf("FIRST(%c) = { %s }\n", i + 'A', firsts[i]);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < 26; i++)
        if (doneFollow[i])
            printf("FOLLOW(%c) = { %s }\n", i + 'A', follows[i]);
}
