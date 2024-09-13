#include <stdio.h>
#include <string.h>

/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
    int n;

    for (n = strlen(s) - 1; n >= 0; n--)
        if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}

int main(void) {
    char a[] = "Carlos Escalante     \n  ";
    printf("%s", a);
    int new_len = trim(a);
    printf("%s", a);
    printf("END\n");
    printf("new len: %d", new_len);
    return 0;
}