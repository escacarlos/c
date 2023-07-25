#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion.
*/

#define MAXOP 100  // max size of operand or operator
#define MAXVAL 100 // maximum depth of val stack

int sp = 0;         // next free stack position
double val[MAXVAL]; // value stack

void push(double f);
double pop(void);

// reverse Polish calculator
int main()
{
    printf("Reverse Polish calculator usage:\nConvert something like (1 - 2) * (4 + 5) to 1 2 - 4 5 + * for reverse Polish notation\n");
    printf("This calculator supports adding (+) subtracting (-) multiplying (*) dividing (/) modulo operation (%%), exponentiation (^),\n");
    printf("exponential function (e), square root function (r), sine operation (s), cosine operation (o), tangent operation (t),\n");
    printf("absolute value function (a), common logarithm (l), natural logarithm (n), ceiling operation (c), and flooring operation (f)\n");
    double op2, num;
    char s[MAXOP], c;

    while (scanf("%s%c", s, &c) == 2) // found something. If EOF provided, this loop will terminate. However, if \n is provided, it will not terminate
    {
        if (sscanf(s, "%lf", &num) == 1) // found a number
            push(num);
        else if (strlen(s) == 1) // found an operator
        {
            switch (*s)
            {
            case '+':
                push(pop() + pop());
                break;
            case '-': /* In push(pop() - pop());, the order in which the two calls of pop are evaluated is not defined. So get op2 first then process */
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case '^':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case 'r':
                push(sqrt(pop()));
                break;
            case 's':
                push(sin(pop()));
                break;
            case 'o':
                push(cos(pop()));
                break;
            case 't':
                push(tan(pop()));
                break;
            case 'a':
                push(fabs(pop()));
                break;
            case 'l':
                push(log10(pop()));
                break;
            case 'n':
                push(log(pop()));
                break;
            case 'c':
                push(ceil(pop()));
                break;
            case 'f':
                push(floor(pop()));
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }
        else
            printf("Unsupported operator: %s\n", s);
        if (c == '\n')
            printf("\t%.8g\n", pop());
    }
    return 0;
}

// push: push f onto value stack
void push(double f)
{
    if (sp < MAXVAL) // if value stack still has space, add f
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void)
{
    if (sp > 0) // if the next free stack position is greater than zero, return the highest level item from stack
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}