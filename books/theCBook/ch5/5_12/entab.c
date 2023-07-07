/* entab.c */

#include <stdio.h>
#include "tabstops.h"

int main(int argc, char *argv[])
{
    int col, c, nspace;

    parsestops(argc, argv);

    col = nspace = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\b' && col > 0)
        {
            --col;
            if (nspace > 0)
                --nspace;
            else
                putchar(c);
        }
        else if (nspace > 0 && istabstop(col))
        {
            if (nspace == 1)
                putchar(' ');
            else
                putchar('\t');
            nspace = 0;
        }
        if (c == '\t')
        {
            putchar(c);
            nspace = 0;
            col = col + dist2stop(col);
        }
        else if (c == ' ')
        {
            ++col;
            ++nspace;
        }
        else if (c != '\b')
        {
            for (; 0 < nspace; --nspace)
                putchar(' ');
            putchar(c);
            if (c == '\n')
                col = 0;
            else
                ++col;
        }
    }
    return 0;
}