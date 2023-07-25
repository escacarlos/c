#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard
    input. Should the file name be printed when a matching line is found?
*/

#define MAXLEN 1000
#define MAXFILES 100

int getline(char *line, int max, FILE *fp);

FILE *fp[MAXFILES] = {0}; // array of FILE pointers initialized to null
int names[MAXFILES];
int fpIndex = 0;

// print lines that match pattern. Source can be files or stdin
int main(int argc, char *argv[])
{
    char line[MAXLEN], pattern[MAXLEN] = {0};
    unsigned long lineNum = 0;
    int invert = 0, number = 0, found = 0, files = 0;
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-v") == 0)
        {
            invert = 1;
            files = 0;
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            number = 1;
            files = 0;
        }
        else if (strcmp(argv[i], "-f") == 0)
            files = 1;
        else if (i + 1 == argc)
            strncpy(pattern, argv[i], MAXLEN - 1); // strncpy doesn't guarantee the string will be null terminated, so don't bother copying the last char from argv
        else if (files == 1)                       // add file pointer
        {
            if (fpIndex < MAXFILES)
            {
                if ((fp[fpIndex] = fopen(argv[i], "r")) == NULL)
                {
                    fprintf(stderr, "can't open %s\n", argv[i]);
                    exit(1);
                }
                names[fpIndex++] = i; // capture the index of the file name to use for printing later
            }
            else
            {
                fprintf(stderr, "too many input files, max supported is %d\n", MAXFILES);
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "usage: find [-v] [-n] [-f file1 [file2] [file3] [...]] pattern\n");
            exit(1);
        }
    if (pattern[0] == '\0' || (files == 1 && fp[0] == NULL)) // no pattern found or no file pointers despite the provided -f argument
    {
        fprintf(stderr, "usage: find [-v] [-n] [-f file1 [file2] [file3] [...]] pattern\n");
        exit(1);
    }
    if (fpIndex == 0) // if no input files, default to stdin
        fp[fpIndex] = stdin;
    for (int i = 0; i < MAXFILES && fp[i] != NULL; i++)
    {
        lineNum = 0;
        while (getline(line, MAXLEN, fp[i]) > 0)
        {
            lineNum++;
            if ((strstr(line, pattern) != NULL) != invert) // strstr(s, t) returns a pointer to the first occurrence of the string t in the string s, or NULL if there is none.
            {
                if (fpIndex > 0) // files were provided
                {
                    if (number)
                        printf("%s %03ld: %s", argv[names[i]], lineNum, line);
                    else
                        printf("%s: %s", argv[names[i]], line);
                }
                else
                {
                    if (number)
                        printf("%03ld: ", lineNum);
                    printf("%s", line);
                }
                found++;
            }
        }
    }
    return found;
}

// read a line, return length
int getline(char *line, int max, FILE *fp)
{
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
        return strlen(line);
}