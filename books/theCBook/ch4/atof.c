#include <ctype.h>
#include <stdio.h>
#include <math.h>

/* atof: convert string s to double */
double atof_c(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

/* atoi: convert string s to integer using atof */
int atoi(char s[])
{
    double atof_c(char s[]);
    return (int) atof_c(s);
}

double atof_exp(char s[])
{
    double val, power, exponent;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    for ( ; isspace(s[i]); i++) /*skip any further white space up to an e or E*/
		;
        
	if ((s[i] != '\0') && (tolower(s[i++]) == 'e')) /*** See 1 below ***/
        exponent = atof_exp(&s[i]);                 /*** See 2 below ***/
	else 
		exponent = 0.0;

	return (sign * val / power) * pow(10.0,exponent);

    /* 1: Just in case we arrive at '\0' and , by some coincidence, the next char in memory 
    happens to be 'e', we should stop or there would be problems i.e. we should only get 
    the exponent if we are still inside s.*/

    /* 2: Note the recursion here; for an original argument of "52.553 e -8.35", this line
    will pass the string " -8.35" and return -8.35 as double.  If the exponent is omitted
    and a string of whitespace/an empty string is passed here, then 0.0 is returned.*/
}

int main(void) {

	char num[] = "1288644.345 e -5.337";

	printf("%.12f\n",atof_exp(num));

	return 0;
}

