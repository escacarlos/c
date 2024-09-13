/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p
set to the rightmost n bits of y, leaving the other bits unchanged. */

#include <stdio.h>
unsigned setbits(unsigned x, int p, int n, unsigned y);
int main()
{
    unsigned int x = 0b10101111, y = 0b00110101;
    int p = 2, n = 3;
    printf("x = %u & y = %u \n", x, y);
    printf("Updated x = ");
    printf("%u\n", setbits(x, p, n, y));
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return ((x & (~0 << (p + n)) | (~(~0 << p))) | ((y & ~(~0 << n)) << p));
}