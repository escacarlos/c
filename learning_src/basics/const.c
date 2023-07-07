/* 

Defining Constants
There are two simple ways in C to define constants −

    -Using #define preprocessor.

    -Using const keyword.

The #define Preprocessor

Given below is the form to use #define preprocessor to define a constant −

#define identifier value

Note that it is a good programming practice to define constants in CAPITALS
*/

#include <stdio.h>

#define LENGTH 10   
#define WIDTH  5
#define NEWLINE '\n'

int main() {
   int area;  
  
   area = LENGTH * WIDTH;
   printf("value of area : %d", area);
   printf("%c", NEWLINE);

   const int  LENGTHy = 10;
   const int  WIDTHy = 5;
   const char NEWLINEy = '\n';
      
   area = LENGTHy * WIDTHy;
   printf("value of area : %d", area);
   printf("%c", NEWLINEy);

   return 0;
}