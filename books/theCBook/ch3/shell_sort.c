#include <stdio.h>

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}


int main(void) {
    int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(a)/sizeof(int);
    printf("len: %d ", len);
    shellsort(a, len);
    printf("array sorted: [");
    for (int i = 0; i < len - 1; ++i) {
        printf(" %d,", a[i]);
    }
    printf(" %d]", a[len - 1]);
    return 0;
}
