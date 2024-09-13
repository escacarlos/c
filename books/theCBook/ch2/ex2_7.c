/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted
(i.e., 1 changed into 0 and vice versa), leaving the the others unchanged.) */
#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned x = 0b11111111;
    int p = 2, n = 3;
    printf("x = %u, p = %d, n = %d\n", x, p, n);
    printf("Inverted x by %d bits starting form position %d = %u", n, p, invert(x, p, n));
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return (x ^ (~(~0 << n) << p));
}