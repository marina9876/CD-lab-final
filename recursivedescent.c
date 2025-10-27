#include <stdio.h>
#include <string.h>

char inp[100];
int curr = 0;

// Function declarations
int E();
int E_();
int T();
int T_();
int F();

int main()
{
    printf("Enter input:\n");
    scanf("%s", inp);

    int res = E();

    // if all characters are consumed and parsing succeeded
    if (res == 1 && curr == strlen(inp))
        printf("Input has been accepted.\n");
    else
        printf("Input has been rejected.\n");
    return 0;
}

// E → T E'
int E()
{
    if (T())
    {
        if (E_())
            return 1;
    }
    return 0;
}

// E' → + T E' | - T E' | ε
int E_()
{
    if (inp[curr] == '+' || inp[curr] == '-')
    {
        curr++;
        if (T())
        {
            if (E_())
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    // ε transition
    return 1;
}

// T → F T'
int T()
{
    if (F())
    {
        if (T_())
            return 1;
    }
    return 0;
}

// T' → * F T' | / F T' | ε
int T_()
{
    if (inp[curr] == '*' || inp[curr] == '/')
    {
        curr++;
        if (F())
        {
            if (T_())
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    // ε transition
    return 1;
}

// F → (E) | i
int F()
{
    if (inp[curr] == '(')
    {
        curr++;
        if (E())
        {
            if (inp[curr] == ')')
            {
                curr++;
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else if (inp[curr] == 'i')
    {
        curr++;
        return 1;
    }
    return 0;
}
