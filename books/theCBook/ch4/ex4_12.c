#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_STR 1000
#define MAXSTRING 1000

void itoa(int, char[], int);
void reverse(char[]);

void my_itoa(int n, char s[])
{
    static int i_;
    static int sign_ = 0;


    if (sign_ == 0)  /* Get sign only if this was a non-recursive call (called by a routine other than itself).*/
    {
        sign_ = (n < 0) ? -1 : 1;
        i_ = 0; /* Index is initialized only on non-recursive call. */
    }
    if (n / 10)
        my_itoa(n / 10, s);

    if (sign_ != 0)
    {
        if (sign_ < 0)
            s[i_++] = '-';
        sign_ = 0; /* Reset the sign to get ready for next non-recursive call. */
    }

    s[i_++] = abs(n % 10) + '0';
    s[i_] = '\0';
}

int main()
{
    int ibuf = -12345;
    char istr[MAX_STR];
    istr[0] = '\0';
    printf("Integer: %d\n", ibuf);
    itoa(ibuf, istr, 0);
    printf("String: %s\n", istr);

     int array[22] =
    {   0,
        1,
        2,
        9,
        10,
        11,
        16,
        17,
        21,
        312,
        -0,
        -1,
        -2,
        -9,
        -10,
        -11,
        -16,
        -17,
        -21,
        -312,
        INT_MAX,
        INT_MIN,
        };

    int i;
    char s[MAXSTRING];

    for (i = 0; i < 22; ++i)
    {
        my_itoa(array[i], s);
        printf("%d    %s\n", array[i], s);
    }
    
    return 0;
}

void itoa(int num, char s[], int pos)
{
    int abs = 0;
    int buf = 0;

    if (num < 0)
    {
        num *= -1;
        abs = EOF;
    }
    buf = num % 10;
    if (buf > 0)
    {
        buf += '0';
        s[pos++] = buf;
        if ((num / 10) > 0)
        {
            /* Reset the sign before recursion so that it is
             * available in the tail of the recursion.*/
            if (abs == EOF)
            {
                num *= -1;
            }
            itoa(num /= 10, s, pos);
        }
        else
        {
            if (abs == EOF)
            {
                s[pos++] = '-';
            }
            s[pos] = '\0';
        }
    }
    if (pos == 1)
    {
        reverse(s);
    };
}

void reverse(char s[])
{
    char c;
    int i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}