#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

char* longestPalindrome(char* s/*, int size*/) 
{
    int n = strlen(s);
    int start = 0, maxlen = 1; // a single leter is a palindrome
    int i, j, k;

    // Allocate memory for the response array
    // char* response = malloc(sizeof(char) * (size + 1)); // +1 for the null terminator
    
    // Alternative to not using malloc (the size of the problem)
    static char response[1001];

    for (i = 0; i < n; i++) {
        j = i, k = i + 1; // even length
        while (j >= 0 && k < n) 
        {
            if (s[j] != s[k])
            {
                break;
            }
            if (k - j + 1 > maxlen)
            {
                start = j;
                maxlen = k - j + 1;
            }
            j--;
            k++;
            printf("first while\n");
            printf("i: %d, j: %d, k: %d\n", i, j, k);
            printf("start: %d, maxlen: %d\n", start, maxlen);
        }
        j = i - 1, k = i + 1; // odd length
        while (j >= 0 && k <= n - 1)
        {
            if (s[j] != s[k])
            {
                break;
            }
            if (k - j + 1 > maxlen)
            {
                start = j;
                maxlen = k - j + 1;
            }
            j--;
            k++;
            printf("second while\n");
            printf("i: %d, j: %d, k: %d\n", i, j, k);
            printf("start: %d, maxlen: %d\n", start, maxlen);
        }
    }

    printf("start: %d, maxlen: %d\n", start, maxlen);

    // Copy the palindrome substring to the response array
    strncpy(response, s + start, maxlen);
    response[maxlen] = '\0';    // Null-terminate the string
    
    return response;
}

int main()
{
    char *str0 = "aabac";
    char *str1 = "a";

    // char *str0_r = longestPalindrome(str0);
    // char *str1_r = longestPalindrome(str1);

    // Correct the expected results in the assertions
    assert(strcmp(longestPalindrome(str0), "aba") == 0);
    assert(strcmp(longestPalindrome(str1), "a") == 0);

    printf("all tests passed!\n");

    // Free the allocated memory
    // free(str0_r);
    // free(str1_r);

    return 0;
}