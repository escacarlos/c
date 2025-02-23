#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 3; // Number of strings
    char **strings = malloc(n * sizeof(char*)); // Allocate memory for string pointers

    // Allocate memory for each string and initialize
    for (int i = 0; i < n; i++) {
        strings[i] = malloc(20 * sizeof(char)); // Each string can hold up to 19 characters + null terminator
        snprintf(strings[i], 20, "String %d", i + 1); // Initialize string
    }

    // Print the strings
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]); // Free each individual string
    }

    free(strings); // Free the array of string pointers
    return 0;
}