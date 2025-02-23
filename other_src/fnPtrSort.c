#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *array, int n, int (*compare)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(array[j], array[j + 1]) > 0) {
                // Swap array[j] and array[j + 1]
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// Comparison function for ascending order
int compareAscending(int a, int b) {
    return a - b; // Returns a positive number if a > b
}

// Comparison function for descending order
int compareDescending(int a, int b) {
    return b - a; // Returns a positive number if b > a
}

void printArray(int *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printArray(array, n);

    // Sort in ascending order
    bubbleSort(array, n, compareAscending);
    printf("Sorted array in ascending order: ");
    printArray(array, n);

    // Sort in descending order
    bubbleSort(array, n, compareDescending);
    printf("Sorted array in descending order: ");
    printArray(array, n);

    return 0;
}