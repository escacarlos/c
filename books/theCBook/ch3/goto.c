/*
for ( ... )
    for ( ... ) {
        ...
        if (disaster)
            goto error;
    }
...
error:
    clean up the mess
*/
#include <stdio.h>
void found(int a[], int b[])
{
    int i, j, m, n;
    int found = 0;
    n = 5;
    m = 5;
    for (i = 0; i < n && !found; i++)
        for (j = 0; j < m && !found; j++)
            if (a[i] == b[j])
                found = 1;
    /* didn′t find any common element */
    
    if (found)
        printf("First common element found: %d", a[i-1]);
    else
        printf("NO COMMON ELEMENTS");
}

void found_goto(int a[], int b[])
{
    int i, j, m, n;
    n = 5;
    m = 5;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (a[i] == b[j])
                goto found;
    /* didn′t find any common element */
    printf("NO COMMON ELEMENTS");
    return;
    found:
    printf("First common element found: %d", a[i]);
}

int main(void) 
{
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {9, 8, 7, 6, 10};
    found(a, b);
    found_goto(a, b);
    return 0;
}
