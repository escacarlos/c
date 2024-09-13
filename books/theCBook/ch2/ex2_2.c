#include <stdio.h>
#define MAXSTRING 1001
#define END 0
#define CONTINUE 1

int check_conditions(void);

int i, lim = MAXSTRING, c;

int main(void)
{
    extern int i, lim, c;
    char s[MAXSTRING];

    for (i = 0; check_conditions() != END; ++i)
        s[i] = c;
    s[i] = '\0';

    printf("%s\n", s);

    return 0;
}

int check_conditions(void)
{
    extern int i, lim, c;
    if (i < lim - 1)
        if ((c = getchar()) != '\n')
            if (c != EOF)
                return CONTINUE;
    return END;
}