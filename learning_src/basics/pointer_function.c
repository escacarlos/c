#include <stdio.h>
#include <time.h>
 
void getSeconds(unsigned long *par);

int main () {

   unsigned long seci;
   getSeconds( &seci );

   /* print the actual value */
   printf("Number of seconds: %ld\n", seci );

   return 0;
}

void getSeconds(unsigned long *par) {
   /* get the current number of seconds */
   *par = time( NULL );         // Check time library
   return;
}