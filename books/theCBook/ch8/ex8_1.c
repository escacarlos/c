#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

/*
    Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open and close instead of their standard library equivalents. Perform experiments to determine
    the relative speeds of the two versions.
*/

enum fileDescriptors { STDIN, STDOUT, STDERR };

void filecopy(int src, int dst);
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
    int f;
    if (argc == 1) // no args; copy standard input to output
        filecopy(STDIN, STDOUT);
    else
        while (--argc > 0)
            if ((f = open(*++argv, O_RDONLY, 0)) == -1)
                error("can't open %s", *--argv);
            else
            {
                filecopy(f, STDOUT);
                close(f); // close the file since finished reading it
            }
    exit(0);
}

// copy src to dst
void filecopy(int src, int dst)
{
    int n;
    char buf[BUFSIZ];
    while ((n = read(src, buf, BUFSIZ)) > 0)
        if (write(dst, buf, n) != n)
            error("unable to copy src to dst");
}

// print an error message and die
void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}