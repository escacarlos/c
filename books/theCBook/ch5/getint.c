#include <ctype.h>
#include <stdio.h> /* for EOF */

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)     /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getint:  get next integer from input into *pn 
 * As written, getint treats a + or - not followed by a digit as a valid 
 * representation of zero. Fix it to push such a character back on the input.
 */
int getint(int *pn)
{
    int c, sign, sawsign;

    while (isspace(c = getch()))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);    /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (sawsign = (c == '+' || c == '-'))
        c = getch();
    if (!isdigit(c)) {
        ungetch(c);
        if (sawsign)
            ungetch((sign == -1) ? '-' : '+');
        return 0;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main()
{
    int number;

	getint(&number);

	printf("%d\n", number);

	return 0;
}