#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int isFinal(int state, int f, int final[]) {
    for (int i = 0; i < f; i++)
        if (final[i] == state)
            return 1;
    return 0;
}

int main() {
    int n, a, f;
    char alphabet[MAX];
    int transition[MAX][MAX], final[MAX];
    int table[MAX][MAX] = {0};

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter alphabet size: ");
    scanf("%d", &a);
    printf("Enter alphabet (no spaces): ");
    scanf("%s", alphabet);

    printf("Enter number of final states: ");
    scanf("%d", &f);
    printf("Enter final states (numbers): ");
    for (int i = 0; i < f; i++)
        scanf("%d", &final[i]);

    printf("Enter transition table (state input -> nextstate):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a; j++) {
            printf("δ(q%d, %c) = ", i, alphabet[j]);
            scanf("%d", &transition[i][j]);
        }
    }

    // Step 1: Mark final vs non-final pairs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (isFinal(i, f, final) != isFinal(j, f, final))
                table[i][j] = 1; // Distinguishable
        }
    }

    // Step 2: Mark remaining distinguishable pairs
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (table[i][j]) continue; // already marked
                for (int k = 0; k < a; k++) {
                    int out1 = transition[i][k];
                    int out2 = transition[j][k];
                    if (table[out1][out2] || table[out2][out1]) {
                        table[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }

    // Step 3: Print equivalent (unmarked) pairs
    printf("\nEquivalent states (can be merged):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (table[i][j] == 0)
                printf("q%d <-> q%d\n", i, j);
        }
    }

    // Step 4: Show distinguishability table
    printf("\nDistinguishability Table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", table[i][j]);
        printf("\n");
    }

    return 0;
}
