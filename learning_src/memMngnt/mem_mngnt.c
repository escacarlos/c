/*
1
void *calloc(int num, int size);
This function allocates an array of num elements each of which size in bytes will be size.

2	
void free(void *address);
This function releases a block of memory block specified by address.

3	
void *malloc(size_t size);
This function allocates an array of num bytes and leave them uninitialized.

4	
void *realloc(void *address, int newsize);
This function re-allocates memory extending it upto newsize.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char name[100];
    char *description;

    strcpy(name, "Zara Ali");

    /* allocate memory dynamically */
    description = malloc( 200 * sizeof(char) );
                //calloc(200, sizeof(char));
        
    if( description == NULL ) {
        fprintf(stderr, "Error - unable to allocate required memory\n");
    } else {
        strcpy( description, "Zara ali a DPS student in class 10th");
    }
    
    printf("Name = %s\n", name );
    printf("Description: %s\n", description );
}