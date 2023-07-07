/*FILES

Opening Files

*fopen( const char * filename, const char * mode );
	
r: Opens an existing text file for reading purpose.
	
w: Opens a text file for writing. If it does not exist, 
then a new file is created. Here your program will start 
writing content from the beginning of the file.

a: Opens a text file for writing in appending mode. 
If it does not exist, then a new file is created. 
Here your program will start appending content in the existing file content.
	
r+: Opens a text file for both reading and writing.
	
w+: Opens a text file for both reading and writing. 
It first truncates the file to zero length if it exists, 
otherwise creates a file if it does not exist.
	
a+: Opens a text file for both reading and writing. 
It creates the file if it does not exist. 
The reading will start from the beginning but writing can only be appended.

for binary files (like pictures or video)
"rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b"

Closing a File

int fclose( FILE *fp );

Writing a File

int fputc( int c, FILE *fp );
int fputs( const char *s, FILE *fp );

fprintf(FILE *fp,const char *format, ...)
Make sure you have /tmp directory available. 
If it is not, then before proceeding, 
you must create this directory on your machine.


*/

#include <stdio.h>

int main() {
    FILE *fp;

    fp = fopen("test.txt", "w+");
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);
    fclose(fp);

    
    //int fgetc( FILE * fp ); //gets a single character
    //char *fgets( char *buf, int n, FILE *fp );

    //FILE *fp;
    char buff[255];

    fp = fopen("HTML.txt", "r");
    fscanf(fp, "%s", buff); // reads the line until a space is found
    printf("1 : %s\n", buff );

    fgets(buff, 255, (FILE*)fp); // reads an entire line
    printf("2: %s\n", buff );
    fclose(fp);

    fp = fopen("HTML.txt", "r");
    while (fgets(buff, 255, (FILE*)fp) != NULL) {
        printf("%s", buff );
    }
    fclose(fp);

    return 0;
}

/*
For binary input and output:
size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
              
size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
*/
