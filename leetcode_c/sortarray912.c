#include <stdlib.h>
#include <stdio.h>

void sort(int* nums, int numsSize){   
    if (numsSize>1)
    {
        int m=numsSize/2;
        int r=numsSize;

        int L[m];       
        int M[r-m];
        

        for(int i=0; i<m; ++i)
            L[i] = nums[i];
        for(int i=m; i<r; ++i)
            M[i-m] = nums[i];

        sort(L, m);
        sort(M, r-m);

        int i=0, j=0, k=0;
       
        while(i<m && j<r-m)
        {
            if(L[i]<M[j])
            {
                nums[k]=L[i];
                i++;
            }
            else
            {
                nums[k]=M[j];
                j++;
            }
            k++;
        }

        while(i<m)
        {
            nums[k]=L[i];
            i++;
            k++;
        }

        while(j<r-m)
        {
            nums[k]=M[j];
            j++;
            k++;
        }   
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize)
{
    *returnSize=numsSize;
    int* res= (int *)malloc(sizeof(int)*numsSize);
    sort(nums, numsSize);
    for(int i=0; i<numsSize; ++i)
    {
        res[i]=nums[i];
    }
    return res;
}

int main()
{
    int x = 4;
    int* a =(int*)malloc(sizeof(int)*x);
    a[0]=5;
    a[1]=2;
    a[2]=3;
    a[3]=1;
    
    int* ret;
    ret=&x;

    int* res = (int*)malloc(sizeof(int)*4);
    res = sortArray(a, x, ret);
    for(int i=0; i<x; ++i)
        printf("%d, ",res[i]);
    return 0;
}