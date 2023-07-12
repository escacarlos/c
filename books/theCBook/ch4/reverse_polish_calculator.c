// Include up to ex4.5
#include <stdio.h>
#include <stdlib.h> /* for atof and EXIT_SUCCESS */
#include <math.h> /* for fmod and others */
#include <string.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define IDENTIFIER   1

int getop(char[]);
void push(double);
double pop(void);
void showTop(void);
void duplicate(void);
void swapItems(void);
void clearStack(void);
void dealWithName(char s[]);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case IDENTIFIER:
            dealWithName(s);
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
        case '%':
            op2 = pop();
            if(op2)
                push(fmod(pop(), op2));
            else
                printf("\nError: Division by zero!");
            break;
        case '?': 
            showTop();
            break;
        case '#':
            duplicate();
            break;
        case '~':
            swapItems();
            break;
        case '!':
            clearStack();
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return EXIT_SUCCESS;
}

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void showTop(void)
{
    if (sp > 0)
        printf("Top of stack contains: %8g\n", val[sp-1]);
    else
        printf("The stack is empty!\n");
}

/*
Alternatively:
void showTop(void)
{
    double item = pop();
    printf("Top of stack contains: %8g\n", item);
    push(item);
}  
*/

void duplicate(void)
{
    double temp = pop();
    push(temp);
    push(temp);
}

void swapItems(void)
{
    double item1 = pop();
    double item2 = pop();
    push(item1);
    push(item2);
}

/* pop only returns a value if sp is greater than zero. So setting the stack pointer to zero will cause pop to return its error */

void clearStack(void)
{
    sp = 0;
}

/* deal with a string/name this may be either a maths function or for future exercises: a variable */
void dealWithName(char s[])
{
   double op2;
   
   if( 0 == strcmp(s, "sin"))
      push(sin(pop()));
   else if( 0 == strcmp(s, "cos"))
      push(cos(pop()));
   else if (0 == strcmp(s, "exp"))
      push(exp(pop()));
   else if(!strcmp(s, "pow"))
   {
      op2 = pop();
      push(pow(pop(), op2));
   }
   else
      printf("%s is not a supported function.\n", s);
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c, next;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    /* not a number but may contain a unary minus */
    if (!isdigit(c) && c != '.' && c != '-')
        return c; 

    if (c == '-')
    {
        next = getch();
        if (!isdigit(next) && next != '.')
        {
            return c;
        }
        c = next;
    }
    else
        c = getch();

    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */


int getch(void)     /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
/* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}