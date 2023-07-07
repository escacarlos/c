#include <stdio.h>

int main()
{
    int c;
    c=getchar()!=EOF;

    printf("%d %d", c, EOF);
}