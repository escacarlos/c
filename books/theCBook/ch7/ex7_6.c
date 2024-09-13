#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Exercise 7-6. Write a program to compare two files, printing the first line where they differ.
*/

#define MAXLINE 1000

int getline(char *line, int max, FILE *fp);

int main(int argc, char *argv[])
{
    if (argc != 3) // wrong amount of arguments
    {
        printf("usage: diff file1 file2\n");
        return 1;
    }

    FILE *fp1 = fopen(argv[1], "r"), *fp2 = fopen(argv[2], "r");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("error: failed to open %s\n", fp1 == NULL ? argv[1] : argv[2]);
        exit(1); // calls fclose on open file pointers
    }

    int status1 = 1, status2 = 1, lineNum = 0;
    char line1[MAXLINE], line2[MAXLINE];
    while (status1 != 0 && status2 != 0)
    {
        lineNum++;
        status1 = getline(line1, MAXLINE, fp1);
        status2 = getline(line2, MAXLINE, fp2);
        if (status1 == 0 && status2 == 0)
            printf("%s and %s are the same files!\n", argv[1], argv[2]);
        else if (status1 == 0)
            printf("%s file ended but %s file has:\n%d: %s", argv[1], argv[2], lineNum, line2);
        else if (status2 == 0)
            printf("%s file ended but %s file has:\n%d: %s", argv[2], argv[1], lineNum, line1);
        else if (strcmp(line1, line2) != 0)
        {
            printf("Files differ on line %d. %s has:\n%s%s has:\n%s", lineNum, argv[1], line1, argv[2], line2);
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

// read a line, return length
int getline(char *line, int max, FILE *fp)
{
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
        return strlen(line);
}