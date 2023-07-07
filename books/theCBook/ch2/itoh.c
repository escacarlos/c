#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert(int);

int main()
{
    int n, length;
    char *hex;
    printf("Enter a decimal number: ");
    scanf("%d", &n);
    hex = convert(n);
    length=strlen(hex);
    printf("%d in decimal = %s in hexadecimal %d\n", n, hex, length);
    return 0;
}

char* convert(int n)
{
    static char hex[100];
    char temp[100];
    int rem, j, k=2, i=0;

    while(n!=0)
    {
        rem=n%16;
        if(rem<10)
            temp[i++]='0'+rem;
        else
            temp[i++]='A'+rem-10;
        n/=16;
    }    
    hex[0]='0';
    hex[1]='X';
    for(j=strlen(temp)-1;j>=0;j--)
        hex[k++]=temp[j];
    hex[i+2]='\0';
    return hex;
}