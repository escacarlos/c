#include <cstdio>
//#include "stack.cc" // if the size can not be predicted

#define max 100

// if the size of the stack can be predicted
static int stack[max + 1], p;
auto push(int v)
{
    stack[p++] = v;
}
int pop()
{
    return stack[--p];
}
auto stackinit()
{
    p = 0;
}
int stackempty()
{
    return !p;
}

int main()
{
    char c;
    int x;
    for (stackinit(); scanf("%1s", &c) != EOF;)
    {
        x = 0;
        if (c == '+')
            x = pop() + pop();
        if (c == '*')
            x = pop() * pop();
        while (c >= '0' && c <= '9')
        {
            x = 10 * x + (c - '0');
            scanf("%1c", &c);
        }
        push(x);
    }
    printf("%d\n", x);
}