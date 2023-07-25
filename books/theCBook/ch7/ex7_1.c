#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
    Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0].
*/

enum type
{
    LOWER,
    UPPER
};

int main(int argc, char *argv[])
{
    int c, mode = -1;
    if (argc > 1)
    {
        printf("usage 1: ./lower\nusage 2: .\\lower.exe\nusage 3: ./upper\nusage 4: .\\upper.exe\n");
        return 1;
    }
    if (stricmp(*argv, "lower") == 0 || stricmp(*argv, "lower.exe") == 0) // handles when argv simply equals the executable name
        mode = LOWER;
    else if (stricmp(*argv, "upper") == 0 || stricmp(*argv, "upper.exe") == 0) // handles when argv simply equals the executable name
        mode = UPPER;
    else // handles when argv has a relative or absolute path for the executable
    {
        while (*++*argv != '\0') // go to end of string
            ;
        while (*--*argv != '\\' && **argv != '/') // go back until a slash is found
            ;
        (*argv)++; // move right to not include the slash
        if (stricmp(*argv, "lower") == 0 || stricmp(*argv, "lower.exe") == 0)
            mode = LOWER;
        else if (stricmp(*argv, "upper") == 0 || stricmp(*argv, "upper.exe") == 0)
            mode = UPPER;
    }
    if (mode == LOWER)
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    else if (mode == UPPER)
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    else
    {
        printf("usage 1: ./lower\nusage 2: .\\lower.exe\nusage 3: ./upper\nusage 4: .\\upper.exe\n");
        return 1;
    }
    return 0;
}