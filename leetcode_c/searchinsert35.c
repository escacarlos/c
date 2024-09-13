#include <stdio.h>

int searchInsert(int* nums, int numsSize, int target){
    int i;
    if(target==nums[numsSize-1])
        return numsSize-1;        
    else if(target>nums[numsSize-1])
        return numsSize;
    for(i=0; i<numsSize; ++i)
    {
        if(nums[i]==target)
            return i;
        else if(target>nums[i] && target<nums[i+1])
            return i+1;
    }
    return 0;
}

int main()
{
    int nums[4] = {1,3,5,6};
    int res = searchInsert(nums, 4, 5);
    printf("%d\n",res);
}