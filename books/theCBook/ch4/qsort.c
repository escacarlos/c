#include <stdio.h>
void print(int a[], int n);
/* qsort: sort v[left]...v[right] into increasing order */
static int sN = 0;
void qsort(int v[], int left, int right)
{
    int i, j, last;
    void swap(int v[], int i, int j);
    if(left >= right) /* do nothing if array contais */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2); /* move partition elem */
    
    print(v, right);
    
    last = left;        /* to v[0] */
    for(i = left + 1; i <= right; i++)  /* partition */
    {    
        if(v[i] < v[left])
        {
            swap(v, ++last, i);
            
            print(v, right);
        }
    }
    swap(v, left, last);    /* restore partition elem */
    
    print(v, right);
    
    qsort(v, left, last -1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i]=v[j];
    v[j]=temp;
}

void print(int a[], int n)
{    
    ++n;
    printf("swap %d: ", sN);
    int i = 0;
    while(i<n) {
        printf("%d", a[i]);
        ++i;
    }
    printf("\n");
    ++sN;
}

int main()
{
    int a[] = {8, 7, 6, 4, 3, 2, 1};
    int n = 6;
    printf("Original array to sort: ");
    print(a, n);
    qsort(a, 0, n);
    print(a, n);
    printf("\n");
}
