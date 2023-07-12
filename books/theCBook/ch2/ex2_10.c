/* Rewrite the function lower, which convers upper case letters to lower case,
with a conditional expression instead of if-else. */
#include <stdio.h>

int lower(int c);

int main()
{
    int c = 'A';
    printf("%c", lower(c));
    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c += 'a' - 'A' : c;
}