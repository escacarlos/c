#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);
void stakop(int);

int nopprint = 0; /* don't pop & print on ENTER after stack operations */
double op2, op3;

int main(void)
{
    int type;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '@':
        case '?':
        case '#':
        case '~':
        case '!': /* stack operations */
            stakop(type);
            break;
        case '_': /* unary minus (underscore) negates previous number */
            push(0.0 - pop());
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%': /* floating modulo operator, not integer */
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            if (!nopprint)
                printf("\t%.8g\n", pop());
            nopprint = 0;
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 1;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
    return;
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c, type;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ; /* skip leading spaces or tabs */
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* was operator */
    i = 0;        /* was digit    */

    if (isdigit(c))
    {
        type = NUMBER;
        while (isdigit(s[++i] = c = getch()))
            ; /* get digits   */
    }
    if (c == '.')
    {
        type = NUMBER;
        while (isdigit(s[++i] = c = getch()))
            ; /* and dec pt   */
    }

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return type;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void stakop(int op)
{
    int i;
    nopprint = 1; /* disable pop & print on '\n' */

    switch (op)
    {
    case '@': /* show whole stack (not required by K&R)*/
        if (sp)
        {
            putchar('\n');
            for (i = sp - 1; i >= 0; i--) /* last in, first shown */
                printf("*** %.8g\n", val[i]);
        }
        else
            printf("stack empty\n");
        return;
    case '?': /* print top item */
        if (sp)
        {
            putchar('\n');
            push(op2 = pop());
            printf("*** %.8g\n", op2);
        }
        else
            printf("stack empty\n");
        return;
    case '#': /* dup top item */
        push(op2 = pop());
        push(op2);
        return;
    case '~': /* swap top 2 items */
        op2 = pop();
        op3 = pop();
        push(op2);
        push(op3);
        return;
    case '!': /* clear stack */
        nopprint = 0;
        sp = 0;
        return;
    default: /* should only get here if there's a bug */
        printf("error: unknown command %s\n", op);
        return;
    }
}