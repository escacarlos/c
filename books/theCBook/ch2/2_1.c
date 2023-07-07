#include <stdio.h>
#include <math.h>
#include <string.h>

/*strlen: return length of s*/
int strlen_c(char s[])
{
    int i;
    while(s[i]!='\0')
        ++i;
    return i;
}
/*<string.h>*/

enum boolean {NO, YES};
/*<stdbool.h*/

enum escapes {BELL='\a', BACKSPACE = '\b', TAB='\t',
            NEWLINE='\n', VTAB='\v', RETURN='\r'};

enum months {JAN=1, FEB, MAR, APR, MAY, JUN,
            JUL, AUG, SEP, OCT, NOV, DEC};
            /*FEB=2, MAR=3, etc.*/

/*atoi: convert s to integer*/
int atoi_c(char s[])
{
    int i, n;

    n=0;
    for(i=0; s[i]>='0' && s[i]<='9'; ++i)
        n=10*n + (s[i]-'0');
    return n;
}

int htoi(char s[])
{
    int dec, i, n, p, length;

    p=1;
    n=0;
    length=strlen_c(s);

    for(i=length-1; i>=0; --i)
    {
        
        if(s[i]>='A' && s[i]<='F') {
            n+=(s[i]-'A'+10)*p;
            p*=16;
        }
        else if(s[i]>='a' && s[i]<='f') {
            n+=(s[i]-'a'+10)*p;
            p*=16;
        }
        else if(s[i]>='0' && s[i]<='9'){
            n+=(s[i]-'0')*p;
            p*=16;
        }
    }
    return n;
}

int btoi(char s[])
{
    int dec, i, n, p, length;

    p=1;
    n=0;
    length=strlen_c(s);

    for(i=length-1; i>=0; --i)
    {
        if(s[i]>='0' && s[i]<='1'){
            n+=(s[i]-'0')*p;
            p*=2;
        }
    }
    return n;
}

int btoi2(long long n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
    return dec;
}

/*lower: convert c to lower case; ASCII only*/
int lower(int c)
{
    if(c>='A' && c<= 'Z')
        return c+'a'-'A';
    else
        return c;
}
/*<ctype.h> isdigit(c)*/

int upper(int c)
{
    if(c>='a' && c<='z')
        return c-'a'-'A';
    else
        return c;
}



/*squeeze: delete all c from s*/
void squeeze(char s[], int c)
{
    int i, j;

    for(i=j=0; s[i] != '\0'; i++)
        if(s[i]!=c)
            s[j++]=s[i];
    s[j]='\0';
}

void squeeze2(char s1[], char s2[])
{
    int i, j, k;

    for(k=0; s2[k]!='\0';k++)
        for(i=j=0; s1[i] != '\0'; i++)
            if(s1[i]!=s2[k])
                s1[j++]=s1[i];
    s1[--j]='\0';
}

void squeeze3(char s1[], char s2[])
{
    int k;
    for(k=0; s2[k]!='\0';k++)
        squeeze(s1, s2[k]);
}

/*strcat: concatenate t to end of s; s must be big enough*/
void strcat_c(char s[], char t[])
{
    int i, j;

    i=j=0;
    while(s[i]!='\0') /*find end of s*/
        ++i;
    while((s[i++]=t[j++])!='\0') /*copy t*/
        ;
}

int main() {
    char s[100] = "0x1101";
    char s1[50] = "Carlos Alfredo";
    char s2[10] = "rl";
    int dec;
    
    dec = btoi2(atoi_c(s));
    squeeze(s1, 'C');
    squeeze2(s1, s2);

    printf("%s\n", s1);
    return 0;
}