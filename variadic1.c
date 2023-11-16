#include <stdarg.h>
#include <stdio.h>

// Variadic function to add numbers
int add_numbers(int n, ...)
{
    int sum = 0;
    
    // Declaring pointer to the argument list
    va_list ptr;

    // Initializing argument to the list pointer
    va_start(ptr, n);
    
    for(int i = 0; i < n; i++)
    {
        // Accessing current variable and pointing to the next one
        sum += va_arg(ptr, int);
    }

    // Ending argument list traversal
    va_end(ptr);

    return sum; 
}

// Driver code
int main(int argc, char* argv[])
{
    printf("\n\n Variadic function: \n");

    // Variadic number of arguments
    printf("\n 1 + 2 = %d ", add_numbers(2, 1, 2));

    printf("\n 3 + 4 + 5 = %d ", add_numbers(3, 3, 4, 5));

    printf("\n 6 + 7 + 8 + 9 = %d ", add_numbers(4, 6, 7, 8, 9));

    printf("\n");

    return 0;
}