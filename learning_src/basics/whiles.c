#include <stdio.h>
#include <stdbool.h>
 
int main () {

    /* local variable definition */
    int a = 10;
    int i, j;
       
    /* while loop execution */
    while( a < 20 ) {
        printf("111111111value of a: %d\n", a);
        a++;
    }

    /* for loop execution */
    for( i = 10; i < 20; i = i + 1 ){
        printf("222222value of i: %d\n", i);
    }
 
    do {
        printf("33333333333333value of a: %d\n", a);
        a = a + 1;
    }while( a < 40 );
    
    //int modulo;
    bool B;
    float modulo;
    for(int k = 2; k<100; k++) {
        printf("\nbefore inner loop -> k = %d\n", k);
        for(j = 2; j <= (k/j); j++) 
        {
            printf("inside the inner loop -> k = %d, j = %d\n", k, j);
            if(B=!(k%j))
            {
                printf("%d ", B);
                printf(B ? "true " : "false ");
                printf("%s", B ? "true " : "false ");
                fputs(B ? "true\n" : "false\n", stdout);
                modulo = k%j;
                printf("modulo = %.3f\n", modulo);
                break;
            }          // if factor found, not prime
        }
        
        
        printf("after inner loop -> k = %d, j = %d\n", k, j);
        if(j > (k/j)) printf("***************** %d is prime\n", k);
    }
   return 0;
}

/* Nested loops

for ( init; condition; increment ) {

   for ( init; condition; increment ) {
      statement(s);
   }
   statement(s);
}

while(condition) {

   while(condition) {
      statement(s);
   }
   statement(s);
}

do {
   statement(s);

   do {
      statement(s);
   }while( condition );

}while( condition );
*/