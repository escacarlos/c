#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5; // Number of integers
    int *numbers = malloc(n * sizeof(int)); // Allocate memory for integers

    // Initialize the array
    for (int i = 0; i < n; i++) {
        numbers[i] = i * 10; // Assign values
    }

    // Print the integers
    for (int i = 0; i < n; i++) {
        printf("%d\n", numbers[i]);
    }

    free(numbers); // Free the allocated memory
    return 0;
}
