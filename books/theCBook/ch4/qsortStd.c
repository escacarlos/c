#include <stdlib.h>
#include <stdio.h>

/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int compare_ints(const void *p, const void *q)
{
    int x = *(const int *)p;
    int y = *(const int *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (x < y)
        return -1; // Return -1 if you want ascending, 1 if you want descending order.
    else if (x > y)
        return 1; // Return 1 if you want ascending, -1 if you want descending order.

    return 0;
    // All the logic is often alternatively written:
    return (x > y) - (x < y);
}

/* Sort an array of n integers, pointed to by a. */
void sort_ints(int *a, size_t n)
{
    qsort(a, n, sizeof(*a), compare_ints);
}

int main()
{
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n = 10;
    sort_ints(a, n);
    int i = 0;
    while(i<n) {
        printf("%d", a[i]);
        ++i;
    }
}