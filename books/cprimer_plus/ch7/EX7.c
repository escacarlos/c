#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char ch;
    int lc = 0; // lowercase char count
    int uc = 0; // uppercase char count
    int sc = 0; // space count 
    int oc = 0; // other char count
    while ((ch = getchar()) != '#')
    {
        if (ch >= 'a' && ch <= 'z')
            lc++;
        else if (ch >= 'A' && ch <= 'Z')
            uc++;
        else if (isspace(ch))
            sc++;
        else
            oc++;
    }
    printf("%d lowercase, %d uppercase, %d spaces, %d other", lc, uc, sc, oc);
    return 0;
}