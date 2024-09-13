/* Write a function rightrot(x,n) that returns the value of the
integer rotated to the right by n bit positions. */

#include <stdio.h>

unsigned rightrot(unsigned int x, int n);
int binlen(unsigned x);

int main()
{
    unsigned int x = 0b10001111;
    int n = 4;
    printf("x = %u\nRotated x = %u by %d bit = %u\n", x, x, n, rightrot(x, n));
    return 0;
}

unsigned rightrot(unsigned int x, int n)
{
    return (x | (x & ~(~0 << n)) << binlen(x)) >> n;
}

int binlen(unsigned x)
{
    int i, temp = 1;
    for (i = 0; x >= (temp = temp * 2); i++)
        ;
    return i + 1;
}