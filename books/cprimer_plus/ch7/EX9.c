#include <stdio.h>
int main(void)
{
    char ch;
    while ((ch = getchar()) != '#')
    {
        if (ch == 'b')
        {
            printf("Step 1\n");
            break;
        }
        switch(ch)
        {
            case '\n':
                break;
            case 'c':
                printf("Step 1\n");
                break;
            case 'g':
                printf("Step 1\n");
                printf("Step 3\n");
                break;
            default:
                printf("Step 1\n");
                printf("Step 2\n");
                printf("Step 3\n");
                break;
        }
        ch = getchar();
    }
    printf("Done\n");
    return 0;
}