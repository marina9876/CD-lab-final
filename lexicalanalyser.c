#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[])
{
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while"};
    int i;
    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    char c, buffer[31], operators[] = "+-*/%=";
    int i, j = 0;
    char input[200];

    printf("Enter the program (end input with $):\n");
    scanf("%[^$]", input); // ✅ reads everything until '$'

    int len = strlen(input);

    for (int k = 0; k < len; ++k)
    {
        c = input[k];

        for (i = 0; i < 6; ++i)
        {
            if (c == operators[i])
                printf("%c is operator\n", c);
        }

        if (isalnum(c))
        {
            buffer[j++] = c;
        }
        else if ((c == ' ' || c == '\t' || c == '\n') && (j != 0))
        {
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer) == 1)
                printf("%s is keyword\n", buffer);
            else if (isdigit(buffer[0]))  // ✅ number check
                printf("%s is number\n", buffer);
            else
                printf("%s is identifier\n", buffer);
        }
    }
    return 0;
}
