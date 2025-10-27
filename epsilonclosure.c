#include <stdio.h>
#include <string.h>

char result[20][20], copy[3], states[20][20];
char transitions[50][3][3];  // store all transitions
int transCount = 0;

void add_state(char a[3], int i)
{
    strcpy(result[i], a);
}

int is_present(char a[3], int n)
{
    for (int j = 0; j < n; j++)
    {
        if (strcmp(result[j], a) == 0)
            return 1;
    }
    return 0;
}

void find_closure(char currState[3], int *i)
{
    for (int j = 0; j < transCount; j++)
    {
        if (strcmp(transitions[j][0], currState) == 0 && strcmp(transitions[j][1], "e") == 0)
        {
            if (!is_present(transitions[j][2], *i))
            {
                add_state(transitions[j][2], (*i)++);
                find_closure(transitions[j][2], i);  // recursive for indirect ε transitions
            }
        }
    }
}

void display(int n, char *currState)
{
    int k = 0;
    printf("\nEpsilon closure of %s = {", currState);
    while (k < n)
    {
        printf(" %s", result[k++]);
    }
    printf(" } \n");
}

int main()
{
    char currState[3];
    int i, n, k = 0;
    char state1[3], input[3], state2[3];

    printf("\nEnter the number of states: ");
    scanf("%d", &n);

    printf("\nEnter the states: ");
    for (k = 0; k < n; k++)
        scanf("%s", states[k]);

    printf("\nEnter the number of transitions: ");
    scanf("%d", &transCount);

    printf("\nEnter transitions in format <from> <input> <to> (use 'e' for epsilon):\n");
    for (k = 0; k < transCount; k++)
        scanf("%s %s %s", transitions[k][0], transitions[k][1], transitions[k][2]);

    for (k = 0; k < n; k++)
    {
        i = 0;
        strcpy(currState, states[k]);
        add_state(currState, i++);
        find_closure(currState, &i);
        display(i, currState);
    }

    return 0;
}
