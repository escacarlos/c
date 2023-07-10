#include <stdio.h>

#define MAXLINE 1000
#define MAXLENGTH 81

/* Prints lines over 80 characters */
int getline(char line[], int max);
void copy(char from[], char to[]);

int main()
{
    int len = 0; /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = getline(line, MAXLINE)) > 0)
    {
        if(len > MAXLENGTH)
            printf("LINE-OVER-80-CHARS: %s\n", line);
    }
     
    return 0;
}

int getline(char line[], int max)
{
    int i;
    int c = 0;
    for(i = 0; ((c = getchar()) != EOF) && c != '\n' && i < max - 1; ++i)
        line[i] = c;
    if(c == '\n')
    {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';

    return i;
}
void copy(char from[], char to[])
{
    int i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}