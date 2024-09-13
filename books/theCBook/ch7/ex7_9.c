/*
    Exercise 7-9. Functions like isupper can be implemented to save space or to save time. Explore both possibilities.
*/

// saves time (no function call), but uses more space since the macro is expanded every time it is used (function pointer space vs two part if-statement)
#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0 // Note: don't use because isupper(*++s) would expand to ((*++s) >= 'A' && (*++s) <= 'Z') ? 1 : 0

// saves space, but takes more time due to function call
int isupper_(int c)
{
    return (c >= 'A' && c <= 'Z');
}