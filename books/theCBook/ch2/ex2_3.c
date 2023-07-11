/* Write the function htoi(s), which converts a string of hexadecimal
 * digits (including an optional 0x or 0X) into its equivalent integer
 * value. The allowable digits are 0 through 9, a through f, and
 * A through F.
 *
 * I've tried hard to restrict the solution code to use only what
 * has been presented in the book at this point (page 46). As a
 * result, the implementation may seem a little naive. Error
 * handling is a problem. I chose to adopt atoi's approach, and
 * return 0 on error. Not ideal, but the interface doesn't leave
 * Richard Heathfield much choice.
 *
 * I've used unsigned int to keep the behaviour well-defined even
 * if overflow occurs. After all, the exercise calls for conversion
 * to 'an integer', and unsigned ints are integers!
 */

/* These two header files are only needed for the test driver */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Here's a helper function to get Richard Heathfield around the problem of not
 * having strchr
 */

unsigned long htoi2(const char s[]);

int hexalpha_to_int(int c)
{
    char hexalpha[] = "aAbBcCdDeEfF";
    int i;
    int answer = 0;

    for (i = 0; answer == 0 && hexalpha[i] != '\0'; i++)
    {
        if (hexalpha[i] == c)
        {
            answer = 10 + (i / 2);
        }
    }

    return answer;
}

unsigned int htoi(const char s[])
{
    unsigned int answer = 0;
    int i = 0;
    int valid = 1;
    int hexit;

    if (s[i] == '0')
    {
        ++i;
        if (s[i] == 'x' || s[i] == 'X')
        {
            ++i;
        }
    }

    while (valid && s[i] != '\0')
    {
        answer = answer * 16;
        if (s[i] >= '0' && s[i] <= '9')
        {
            answer = answer + (s[i] - '0');
        }
        else
        {
            hexit = hexalpha_to_int(s[i]);
            if (hexit == 0)
            {
                valid = 0;
            }
            else
            {
                answer = answer + hexit;
            }
        }

        ++i;
    }

    if (!valid)
    {
        answer = 0;
    }

    return answer;
}

/* Solution finished. This bit's just a test driver, so
 * I've relaxed the rules on what's allowed.
 */

int main(void)
{
    char *endp = NULL;
    char *test[] =
        {
            "F00",
            "bar",
            "0100",
            "0x1",
            "0XA",
            "0X0C0BE",
            "abcdef",
            "123456",
            "0x123456",
            "deadbeef",
            "zog_c"};

    unsigned int result;
    unsigned int check;

    size_t numtests = sizeof test / sizeof test[0];

    size_t thistest;

    for (thistest = 0; thistest < numtests; thistest++)
    {
        result = htoi(test[thistest]);
        check = (unsigned int)strtoul(test[thistest], &endp, 16);

        if ((*endp != '\0' && result == 0) || result == check)
        {
            printf("Testing %s. Correct. %u\n", test[thistest], result);
        }
        else
        {
            printf("Testing %s. Incorrect. %u\n", test[thistest], result);
        }
    }

    printf("%ld\n", htoi2("0xFA9C"));
    printf("%ld\n", htoi2("0xFFFF"));
    printf("%ld\n", htoi2("0x1111"));
    printf("%ld\n", htoi2("0xBCDA"));

    return 0;
}

unsigned long htoi2(const char s[])
{
        unsigned long n = 0;

        for (int i = 0; s[i] != '\0'; i++) {
                int c = tolower(s[i]);
                if (c == '0' && tolower(s[i+1]) == 'x')
                        i++;
                else if (c >= '0' && c <= '9')
                        n = 16 * n + (c - '0');
                else if (c >= 'a' && c <= 'f')
                        n = 16 * n + (c - 'a' + 10);
        }
        return n;
}