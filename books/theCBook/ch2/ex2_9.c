/* bitcount:  count 1 bits in x */
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}
/*
Answer:

If x is odd, then (x-1) has the same bit representation as x except that the rightmost 1-bit is now a 0. In this case, (x & (x-1)) == (x-1).

If x is even, then the representation of (x-1) has the rightmost zeros of x becoming ones and the rightmost one becoming a zero. Anding the two clears the rightmost 1-bit in x and all the rightmost 1-bits from (x-1).

Here's the new version of bitcount:
*/
/* bitcount:  count 1 bits in x */
int bitcount_v2(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}

/* In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x.
Explain why. Use this observation to write a faster version of bitcount. */
#include <stdio.h>

int main()
{
    unsigned x = 0b101011;
    printf("%d", bitcount(x));
    printf("%d", bitcount_v2(x));
    return 0;
}