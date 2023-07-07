#include <stdio.h>
int main( ) {

    int c;

    printf( "Enter a value :");
    c = getchar( ); 

    // Doesn't work with "gets" at the same time

    printf( "\nYou entered: ");
    putchar( c );
    printf("\n");

    /*The gets() and puts() Functions
    The char *gets(char *s) function reads a line from stdin 
    into the buffer pointed to by s until either a terminating 
    newline or EOF (End of File).

    The int puts(const char *s) function writes the string 's' and 'a' 
    trailing newline to stdout.

    NOTE: Though it has been deprecated to use gets() function, Instead 
    of using gets, you want to use fgets().*/

    char str1[100];

    printf( "Enter a value :");
    gets( str1 );

    printf( "\nYou entered: ");
    puts( str1 );

    //C library function - fgets()
    //char *fgets(char *str, int n, FILE *stream)
    FILE *fp;
    char str2[60];

    /* opening file for reading */
    fp = fopen("file.txt" , "r");
    if(fp == NULL) {
        perror("Error opening file");
        return(-1);
    }
    if( fgets (str2, 60, fp)!=NULL ) {
        /* writing content to stdout */
        puts(str2);
    }
    fclose(fp);

    /*The int scanf(const char *format, ...) 
    function reads the input from the standard input 
    stream stdin and scans that input according to the
    format provided.

    The int printf(const char *format, ...) 
    function writes the output to the standard outputere stream 
    stdout and produces the output according to the format provided.*/

    char str3[100];
    int i;

    printf( "Enter a value :");
    scanf("%s %d", str3, &i);

    printf( "\nYou entered: %s %d ", str3, i);

    return 0;
}