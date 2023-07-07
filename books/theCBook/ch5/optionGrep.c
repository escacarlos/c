#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

char *my_getline(char *str, int str_max);
/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
        while (my_getline(line, MAXLINE) > 0)
        {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except)
            {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
}

char *my_getline(char *str, int str_max)
{
    char c;
    /*
     * A local variable to perform arithmetic on so that 'str' points to
     * the correct location when it is passed back to the caller.
     */
    char *s1 = str;
    while ((c = getchar()) != EOF && c != '\n' && str_max-- > 0)
    {
        *s1++ = c;
    }

    if (*s1 == '\n')
    {
        *s1++ = c;
    }

    *s1 = '\0';
    return str;
}