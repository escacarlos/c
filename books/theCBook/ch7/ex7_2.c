#include <stdio.h>
#include <ctype.h>

#define FORMAT "%X" // "%X" for hex, "%o" for octal
#define LINELEN 75

/*
    Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according
    to local custom, and break long text lines.
*/

int main()
{
    int c, i = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n') // reset line length counter
            i = 0;
        else if (++i == LINELEN) // check if equal to line length. If so, print new line and reset counter
        {
            i = 0;
            putchar('\n');
        }
        if (isgraph(c) || isspace(c)) // graphic characters and spaces
            putchar(c);
        else
            printf(FORMAT, c); // non-graphic characters
    }
    return 0;
}