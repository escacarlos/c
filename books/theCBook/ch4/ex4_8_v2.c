/* K&R Exercise 4-8 */
/* Jesus Alvarez    */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int main()
{
    char c;

    /*
     * The purpose of getch() and ungetch() is to read characters from
     * getchar() while isdigit or isaplha is true. Once isdigit/isalpha is
     * not true, then reading has gone too far, and it must be pushed back
     * onto the stack for later precessing.
     */
    while ((c = getch()) != EOF)
    {
        if (isdigit(c))
        {
            /*
             * Read until !isdigit(), meaning we have read one
             * character too far.
             */
            putchar(c);
            while (isdigit(c = getch()))
            {
                putchar(c);
            }
            if (c != EOF)
            {
                /* Send it back to the stack for future
                 * processing. */
                ungetch(c);
            }
        }
        else
        {
            /* All other characters. */
            putchar(c);
        }
    }
    return 0;
}

int buf = -2; /* Buffer for getch() */

int getch(void)
{
    int tmp;
    if (buf > -2)
    {
        tmp = buf;
        buf = -2;
        return tmp;
    }
    return getchar();
}

void ungetch(int c)
{
    if (buf > -2)
    {
        printf("Ungetch: Too many characters.\n");
    }
    else
    {
        buf = c;
    }
}