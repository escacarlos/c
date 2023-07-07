#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] =
    {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day)
{
    if (year < 1752)
        return -1;

    int i, leap;
    leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

    if (!((month >= 1 && month <= 12) && (day >= 1 && day <= daytab[leap][month])))
        return -1;

    for (i = 1; i < month; i++)
    {
        day += daytab[leap][i];
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    if (year < 1752)
    {
        *pmonth = *pday = -1;
        return;
    }

    int i, leap;
    leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

    if (!(yearday >= 1 && yearday <= (leap ? 366 : 365)))
    {
        *pmonth = *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

/* month_name: return name of n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"};
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main()
{
    int month, day, year, yearday, retval;

    /******************************* Case 1 *****************************/
    printf("Case 1:\n");
    year = -2017;
    month = 11;
    day = 22;
    yearday = 326;

    retval = day_of_year(year, month, day);
    if (retval == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d %d <---> %d %d\n", year, month, day, year, retval);

    month_day(year, yearday, &month, &day);
    if (month == -1 && day == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d <---> %d %d %d\n", year, yearday, year, month, day);
    printf("\n");
    /*********************************************************************/

    /******************************* Case 2 *****************************/
    printf("Case 2:\n");
    year = 2017;
    month = -11;
    day = 22;
    yearday = 326;

    retval = day_of_year(year, month, day);
    if (retval == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d %d <---> %d %d\n", year, month, day, year, retval);

    month_day(year, yearday, &month, &day);
    if (month == -1 && day == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d <---> %d %d %d\n", year, yearday, year, month, day);
    printf("\n");
    /*********************************************************************/

    /******************************* Case 3 *****************************/
    printf("Case 3:\n");
    year = 2017;
    month = 11;
    day = -22;
    yearday = 326;

    retval = day_of_year(year, month, day);
    if (retval == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d %d <---> %d %d\n", year, month, day, year, retval);

    month_day(year, yearday, &month, &day);
    if (month == -1 && day == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d <---> %d %d %d\n", year, yearday, year, month, day);
    printf("\n");
    /*********************************************************************/

    /******************************* Case 4 *****************************/
    printf("Case 4:\n");
    year = 2017;
    month = 11;
    day = 22;
    yearday = -326;

    retval = day_of_year(year, month, day);
    if (retval == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d %d <---> %d %d\n", year, month, day, year, retval);

    month_day(year, yearday, &month, &day);
    if (month == -1 && day == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d <---> %d %d %d\n", year, yearday, year, month, day);
    printf("\n");
    /*********************************************************************/

    /******************************* Case 5 *****************************/
    printf("Case 5:\n");
    year = 2017;
    month = 11;
    day = 22;
    yearday = 326;

    retval = day_of_year(year, month, day);
    if (retval == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d %d <---> %d %d\n", year, month, day, year, retval);

    month_day(year, yearday, &month, &day);
    if (month == -1 && day == -1)
        printf("Incorrect input\n");
    else
        printf("%d %d <---> %d %d %d\n", year, yearday, year, month, day);
    printf("\n");
    /*********************************************************************/

    return 0;
}

/*
The output of the above program is:
Case 1:
Incorrect input
Incorrect input

Case 2:
Incorrect input
2017 326 <---> 2017 11 22

Case 3:
Incorrect input
2017 326 <---> 2017 11 22

Case 4:
2017 11 22 <---> 2017 326
Incorrect input

Case 5:
2017 11 22 <---> 2017 326
2017 326 <---> 2017 11 22
*/