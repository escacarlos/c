#include <stdio.h>
#include <stdarg.h>

/*
    Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous section.
*/

int minscanf(char *fmt, ...);

int main()
{
    char s[3], c;
    int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10;
    float f1, f2, f3, f4, f5;
    unsigned int u;
    void *p = NULL;
    printf("Copy and paste in the following text to test this program:\n-5 0x6 0X7 7 010 11 11 c D 0xe 0XFg hi 1.920e+001 2.122E+001 2.3 2.4 2.5 %p %%\n", (void *)&c);
    if (minscanf("%d %i %i %i %o %o %u %x %x %x %x %c %s %e %e %f %g %g %p %%", &i1, &i2, &i3, &i4, &i5, &i6, &u, &i7, &i8, &i9, &i10, &c, s, &f1, &f2, &f3, &f4, &f5, &p) != 19)
        printf("Not all inputs were assigned!\n");
    printf("%d %#x %#X %o %#o %o %u %x %X %#x %#X%c %s %.3e %.3E %.1f %g %g %p %%\n", i1, i2, i3, i4, i5, i6, u, i7, i8, i9, i10, c, s, f1, f2, f3, f4, f5, p);
    return 0;
}

// minimal scanf with variable argument list. Returns number of assigned input items
int minscanf(char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    char *p, *sval, format[3] = {'%', '\0', '\0'};
    int *ival, numFound = 0;
    double *dval;
    unsigned int *uival;
    void **vval; // pointer to a pointer

    va_start(ap, fmt); // make ap point to 1st unnamed arg
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
            continue;
        switch (*++p)
        {
        case 'd':
        case 'i':
        case 'c': // char is promoted to int when passed through '...'
            ival = va_arg(ap, int *);
            format[1] = *p;
            numFound += scanf(format, ival);
            break;
        case 'e':
        case 'f':
        case 'g':
            dval = va_arg(ap, double *);
            format[1] = *p;
            numFound += scanf(format, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            numFound += scanf("%s", sval);
            break;
        case 'x':
        case 'o':
        case 'u':
            uival = va_arg(ap, unsigned int *);
            format[1] = *p;
            numFound += scanf(format, uival);
            break;
        case 'p':
            vval = va_arg(ap, void *);
            numFound += scanf("%p", vval);
        case '%': // no need to do anything
            break;
        default:
            printf("unsupported format specifier: %%%c\n", *p);
            break;
        }
    }
    va_end(ap); // clean up when done
    return numFound;
}