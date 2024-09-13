#include <stdio.h>
#include <limits.h>
#include <float.h>

int powerint(int i);       /*type int calcuate limit of int*/
long powerlong(int i);     /*type long calculate limit of long*/
float powerfloat(int i);   /*type float calculate limit of float*/
double powerdouble(int i); /*type double calculate limit of double*/

int main()
{
    char char1, char0;    /*char1 is max char0 is min*/
    short short1, short0; /*short1 is max short0 is min*/
    int int0, i;          /*int0 represent max or min*/
    double d;
    float f;

    char0 = 0;
    for (char1 = 0; char1 <= char0; --char1)
    { /*char type is 8 bits example can shirnks to 4 bits
      -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7
      when char1 equals -8 if subtracts 1 willequals 7
      when char1 equals -8 char0 equals -8
      when char1 equals 7 not less than or equal-8*/
        char0 = char1;
    }
    printf("computation char max %d\n", char1);
    printf("computation char min %d\n\n", char0);

    short0 = 0;
    for (short1 = 0; short1 <= short0; --short1)
        short0 = short1;
    printf("computation short max %d\n", short1);
    printf("computation short min %d\n\n", short0);

    int0 = 0;
    for (i = 0; powerint(i) != 0; ++i) /*if int range is
                                       -4 -3 -2 -1 0 1 2 3
                                       when i == 2 and powerint(i) == 4 will be -4
                                       cause 3 add 1 == -4
                                       when int0 = -4
                                       when i == 3 is
                                       1 2 3 4 5 6 7 8
                                       powerint(3) == 0*/
        int0 = powerint(i);
    printf("computation int max %d\n", int0 - 1);
    int0 = 0;
    for (i = 0; int0 >= (0 - powerint(i)); ++i) /*if int range is
                                                -2 -1 0 1
                                                when i = 1 and powerint(1) == 2
                                                powerint(1) == -2
                                                (0 - powerint(1)) == 2
                                                (0 - powerint(1)) == -2
                                                int0 = -2
                                                when i = 2 and powerint(2) == 4
                                                1 2 3 4
                                                (0 - powerint(2)) == 0*/
        int0 = powerint(i);
    printf("computation int min %d\n\n", int0);

    for (i = 0; powerlong(i) != 0; ++i) /*if long type range is
                                        -2 -1 0 1
                                        when i == 1 and powerlong(1) == 2
                                        powerlong(1) == -2
                                        when powerlong(2)
                                        1 2 3 4
                                        powerlong(2) == 0*/
        ;
    printf("computation long max %ld\n", powerlong(i - 1) - 1); /*i == 2
                                                                powerlong(1) == -2
                                                                powerlong(1) - 1 == 1*/
    printf("computation long min %ld\n\n", powerlong(i - 1));

    printf("char max %d\n", CHAR_MAX);
    printf("char min %d\n", CHAR_MIN);
    printf("unsigned char max %d\n\n", UCHAR_MAX);
    printf("short max %d\n", SHRT_MAX);
    printf("short min %d\n", SHRT_MIN);
    printf("unsigned short max %d\n\n", USHRT_MAX);
    printf("int max %d\n", INT_MAX);
    printf("int min %d\n", INT_MIN);
    printf("unsigned int max %d\n\n", UINT_MAX);
    printf("long max %ld\n", LONG_MAX);
    printf("long min %ld\n", LONG_MIN);
    printf("unsigned long max %.0f\n\n", d = ULONG_MAX);

    printf("float max %f\n", f = FLT_MAX);
    printf("float min %.126f\n", f = FLT_MIN);
    printf("float max exponent %d\n", FLT_MAX_EXP);
    printf("float min exponent %d\n", FLT_MIN_EXP);
    printf("float mantissa digit exponent %d\n", FLT_MANT_DIG);
    printf("float epsilon %.23f\n", FLT_EPSILON);
    printf("double max %f\n", DBL_MAX);
    printf("double min %.1022f\n", DBL_MIN);
    printf("double max exponent %d\n", DBL_MAX_EXP);
    printf("double min exponent %d\n", DBL_MIN_EXP);
    printf("double epsilon %.52f\n", DBL_EPSILON);
    printf("double mantissa digit exponent %.333f\n\n", DBL_MANT_DIG);

    printf("computation max float %f\n", f = powerfloat(127) * (2 - powerfloat(-23))); /*not very understand about this*/
    printf("computation min float %.126f\n", f = powerfloat(-126));
    printf("computation double max %f\n", d = powerdouble(1023) * (2 - DBL_EPSILON));
    printf("computation double min %.1022f\n", d = powerdouble(-1022));
    printf("computation denormalized number min %.149f\n", f = powerfloat(-126) * powerfloat(-23));
    printf("computation denormalized number max %.149f\n\n", f = powerfloat(-126) * (1 - powerfloat(-23)));

    printf("\n#################################################\n");
    
    printf("\nBits of type char: %d\n\n", CHAR_BIT); /* IV */

    printf("Maximum numeric value of type char: %d\n", CHAR_MAX);   /* IV */
    printf("Minimum numeric value of type char: %d\n\n", CHAR_MIN); /* IV */

    printf("Maximum value of type signed char: %d\n", SCHAR_MAX);   /* IV */
    printf("Minimum value of type signed char: %d\n\n", SCHAR_MIN); /* IV */

    printf("Maximum value of type unsigned char: %u\n\n", (unsigned)UCHAR_MAX); /* SF */ /* IV */

    printf("Maximum value of type short: %d\n", SHRT_MAX);   /* IV */
    printf("Minimum value of type short: %d\n\n", SHRT_MIN); /* IV */

    printf("Maximum value of type unsigned short: %u\n\n", (unsigned)USHRT_MAX); /* SF */ /* IV */

    printf("Maximum value of type int: %d\n", INT_MAX);   /* IV */
    printf("Minimum value of type int: %d\n\n", INT_MIN); /* IV */

    printf("Maximum value of type unsigned int: %u\n\n", UINT_MAX); /* RB */ /* IV */

    printf("Maximum value of type long: %ld\n", LONG_MAX); /* RB */   /* IV */
    printf("Minimum value of type long: %ld\n\n", LONG_MIN); /* RB */ /* IV */

    printf("Maximum value of type unsigned long: %lu\n\n", ULONG_MAX); /* RB */ /* IV */

    /* integer types */
	unsigned char c;
	unsigned short s;
	unsigned int ii;
	unsigned long l;
	unsigned long long ll;


	putchar('\n');
	printf("VALUE RANGES FOR INTEGER TYPES\nUPPERCASE comes from <limits.h>\n"
		"lowercase is calculated.\n\n");

	/* char */
	c = ~0;
	c >>= 1;
	printf("signed char:   %4d,           %4d\n",-c-1,c);
	printf("SCHAR_MIN:     %4d, SCHAR_MAX %4d\n",SCHAR_MIN,SCHAR_MAX);
	printf("unsigned char: %4u,           %4u\n",0,c*2+1);
	printf("UCHAR_MAX:                     %4u\n",UCHAR_MAX);
	putchar('\n');

	/* short */
	s = ~0;
	s >>= 1;
	printf("signed short:   %6d,           %6d\n",-s-1,s);
	printf("SHRT_MIN:       %6d, SHRT_MAX: %6d\n",SHRT_MIN,SHRT_MAX);
	printf("unsigned short: %6u,           %6u\n",0,s*2+1);
	printf("USHRT_MAX:                        %6u\n",USHRT_MAX);
	putchar('\n');

	/* int */
	ii = ~0;
	ii >>= 1;
	printf("signed int:    %11d,          %11d\n",-ii-1,ii);
	printf("INT_MIN:       %11d, INT_MAX: %11d\n",INT_MIN, INT_MAX);
	printf("unsigned int:  %11u,          %11u\n",0,ii*2+1);
	printf("UINT_MAX:                            %11u\n",UINT_MAX);
	putchar('\n');

	/* long */
	l = ~0;
	l >>= 1;
	printf("signed long:   %11ld,           %11ld\n",-l-1,l);
	printf("LONG_MIN:      %11ld, LONG_MAX: %11ld\n",LONG_MIN, LONG_MAX);
	printf("unsigned long: %11lu,           %11lu\n",0l,l*2+1);
	printf("ULONG_MAX:                            %11lu\n", ULONG_MAX);
	putchar('\n');


	/* long long */
	ll = ~0;
	ll >>= 1;
	printf("signed long long:   %20lld,            %20lld\n",-ll-1,ll);
	printf("LLONG_MIN:          %20lld, LLONG_MAX: %20lld\n",LLONG_MIN, LLONG_MAX);
	printf("unsigned long long: %20llu,            %20llu\n",0ll,ll*2+1);
	printf("ULLONG_MAX:                                          %20llu\n", ULLONG_MAX);

    return 0;
}

int powerint(int i)
{
    int p;

    p = 1;
    while (i)
    {
        p = p * 2;
        --i;
    }
    return p;
}

long powerlong(int i)
{
    long p;

    p = 1;
    while (i)
    {
        p = p * 2;
        --i;
    }
    return p;
}

float powerfloat(int i)
{
    float p;

    p = 1;
    if (i > 0)
        while (i)
        {
            p = p * 2;
            --i;
        }
    if (i < 0)
        while (i)
        {
            p = p / 2;
            ++i;
        }
    return p;
}

double powerdouble(int i)
{
    double p;

    p = 1;
    if (i > 0)
        while (i)
        {
            p = p * 2;
            --i;
        }
    if (i < 0)
        while (i)
        {
            p = p / 2;
            ++i;
        }
    return p;
}