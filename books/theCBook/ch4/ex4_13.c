#include <stdio.h>
#include <string.h>

/* I noticed the previous Cat 0 solutions relied on supplying extra index 
 * parameters to the function call.  In my opinion, a function for reversing 
 * a string should not have any other parameters other than the string itself.
 * This function relies on static variables to keep track of indices as the
 * function recurses through the levels. The main routine is for testing only. */

void myreverse(char s[])
{
    static int start = 0;
    static int end;

    int temp;

    if (start == 0)
        end = strlen(s) - 1; /* initialize end only when no recursive calls have been made */
    if (end - start > 2)
    {
        start++;
        end--;
        myreverse(s);
        start--; /* Unwind start and end to start reversing from middle of string. */
        end++;   /* Start will eventually wind back to 0 to get ready for next string.*/
    }
    /* Swap letters */
    temp = s[start];
    s[start] = s[end];
    s[end] = temp;
}

void reverse(char s[], int left)
{
        int slen = strlen(s)-1; /* -1 is to compensate for \0. */
        char buf = s[left];
        if (left < slen) {
                reverse(s, left+1);
        }
        if (buf != '\0') {
                s[slen-left] = buf;
        }
        if (left == 0) {
                /* Once execution reaches this point, it is at the end of the
                 * first recursion and the terminating char must be set to
                 * close the string.
                 */
                s[slen+1] = '\0';
        }
}

main() 
{
    char test1[] = "Hello World!";
    char test2[] = "abcd";
    char test3[] = "ab";
    char test4[] = "";

    printf("input: \"%s\"\n", test1);
    myreverse(test1);
    printf("reversed: \"%s\"\n", test1);
    myreverse(test1);
    printf("twice reversed: \"%s\"\n", test1);
    printf("input: \"%s\"\n", test2);
    myreverse(test2);
    printf("reversed: \"%s\"\n", test2);
    myreverse(test2);
    printf("twice reversed: \"%s\"\n", test2);
    printf("input: \"%s\"\n", test3);
    myreverse(test3);
    printf("reversed: \"%s\"\n", test3);
    myreverse(test3);
    printf("twice reversed: \"%s\"\n", test3);
    printf("input: \"%s\"\n", test4);
    myreverse(test4);
    printf("reversed: \"%s\"\n", test4);
    myreverse(test4);
    printf("twice reversed: \"%s\"\n", test4);

    char tstr[] = "Hello, world!";
    printf("%s\n", tstr);
    reverse(tstr, 0);
    printf("%s\n", tstr);
        
    return 0;
}