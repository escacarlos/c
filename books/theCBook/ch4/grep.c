#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* maximum input line length */
int getline_c2(char line[], int max);
int strindex_c(char source[], char searchfor[]);
int strrindex_c(const char s[], const char t[]);
char pattern[] = "ould";
/* pattern to search for */
/* find all lines matching pattern */
int main()
{
    char line[MAXLINE];
    int found = 0;
    printf("%d\n", strindex_c("I stopped dreaming a long long time ago", "long"));
    printf("%d\n", strrindex_c("I stopped dreaming a long long time ago", "long"));
    while (getline_c2(line, MAXLINE) > 0)
        if (strindex_c(line, pattern) >= 0)
        {
            printf("%s", line);
            found++;
        }
    return found;
}
/* getline: get line into s, return length */
int getline_c2(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
/* strindex: return index of t in s, -1 if none */
int strindex_c(char s[], char t[])
{
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int strrindex_c(const char s[], const char t[])
{
    for (int i = strlen(s) - 1, j; i >= 0; i--)
    {
        for (j = 0; s[i + j] == t[j] && t[j]; j++)
            ;
        if (!t[j])
            return i;
    }
    return -1;
}