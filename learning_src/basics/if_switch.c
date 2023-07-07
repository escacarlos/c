#include <stdio.h>
 
int main () {

   /* local variable definition */
   int a = 100;
 
   /* check the boolean condition using if statement */
	
   if( a < 20 ) {
      /* if condition is true then print the following */
      printf("a is less than 20\n" );
   }
   else {
      /* if condition is false then print the following */
      printf("a is not less than 20\n" );
   }
   
   printf("value of a is : %d\n", a);

   // Part 2

   /* local variable definition */
   int c = 100;
   int d = 200;
 
   /* check the boolean condition */
   if( c == 100 ) {
   
      /* if condition is true then check the following */
      if( d == 200 ) {
         /* if condition is true then print the following */
         printf("Value of c is 100 and d is 200\n" );
      }
   }
   
   printf("Exact value of c is : %d\n", c );
   printf("Exact value of d is : %d\n", d );

   // Part 3
    
    /* local variable definition */
    char grade = 'B';

    switch(grade) {
        case 'A' :
            printf("Excellent!\n" );
            break;
        case 'B' :
        case 'C' :
            printf("Well done\n" );
            break;
        case 'D' :
            printf("You passed\n" );
            break;
        case 'F' :
            printf("Better try again\n" );
            break;
        default :
            printf("Invalid grade\n" );
    }
    
    printf("Your grade is  %c\n", grade );

    // Part 4

    /* local variable definition */
    int g = 100;
    int f = 200;
    
    switch(g) {
    
        case 100: 
            printf("This is part of outer switch\n", g );
        
            switch(f) {
                case 200:
                printf("This is part of inner switch\n", f );
            }
    }
    
    printf("Exact value of a is : %d\n", g );
    printf("Exact value of b is : %d\n", f );

   return 0;
}