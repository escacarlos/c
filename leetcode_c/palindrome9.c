#include <string.h>
#include <stdbool.h>
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) /* record sign */
        n = -n;
    /* make n positive */
    i = 0;
    do
    {
        /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0);
    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

bool isPalindrome(int x){
    char entry[80], rev[80];
    bool res;
    res=false;
    if (x<0)
        return res;
    itoa(x, entry);
    int k = 0;
    int n = strlen(entry);
    for(int i=n-1; i>=0; i--)
    {
        rev[k]=entry[i];
        k++;
    }
    rev[k]='\0';
    if(strcmp(entry,rev)==0)
        res=true;
    else
        res=false;
    return res;
}

bool isPalindrome2(int x){
    int r, n, sum=0;
    bool res;
    n=x;
    res=false;
    if (n<0)
        return res;
    while(n>0)
    {
        r=n%10;
        sum=(sum*10)+r;
        n=n/10;
    }
    if (x==sum)
        res=true;
    else
        res=false;
    return res;
}