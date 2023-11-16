#include <stdarg.h>
#include <stdio.h>

// Variadic function to find the largest number
int largest_number(int n, ...)
{
    // Declaring pointer to the argument list
    va_list ptr;

    // Initializing argument to the list pointer
    va_start(ptr, n);

    int max = va_arg(ptr, int);

    for(int i = 0; i < n-1; i++)
    {
        //Accessing the current variable and pointing to next
        int temp = va_arg(ptr, int);
        max = temp > max ? temp : max;
    }

    // End of argument list traversal
    va_end(ptr);

    return max;
}

// Driver code
int main(void)
{
    printf("\n\n Variadic functions: \n");
    
    // Variable number of arguments
    printf("\n %d ", largest_number(2, 1, 2));

    printf("\n %d ", largest_number(3, 3, 4, 5));

    printf("\n %d ", largest_number(4, 6, 7, 8, 9));

    printf("\n");

    return 0;
}