// typedef unsigned char BYTE;
// BYTE  b1, b2;

#include <stdio.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
 
typedef struct Books {
   char title[50];
   char author[50];
   char subject[100];
   int book_id;
} Book;
 
int main( ) {

   Book book;
 
   strcpy( book.title, "C Programming");
   strcpy( book.author, "Nuha Ali"); 
   strcpy( book.subject, "C Programming Tutorial");
   book.book_id = 6495407;
 
   printf( "Book title : %s\n", book.title);
   printf( "Book author : %s\n", book.author);
   printf( "Book subject : %s\n", book.subject);
   printf( "Book book_id : %d\n", book.book_id);

   printf( "Value of TRUE : %d\n", TRUE);
   printf( "Value of FALSE : %d\n", FALSE);

   return 0;
}

/*typedef is limited to giving symbolic names to types 
only where as #define can be used to define alias for 
values as well, q., you can define 1 as ONE etc.

typedef interpretation is performed by the compiler 
whereas #define statements are processed by the 
pre-processor.*/