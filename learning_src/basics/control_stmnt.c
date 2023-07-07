#include <stdio.h>
 
int main () {

    /* local variable definition */
    int a = 10;

    /* while loop execution */
    while( a < 20 ) {
    
        printf("value of a: %d\n", a);
        a++;
            
        if( a > 15) {
            /* terminate the loop using break statement */
            break;
        }
    }
    
    /* local variable definition */
    int b = 10;

    /* do loop execution */
    do {
    
        if( b == 15) {
            /* skip the iteration */
            b = b + 1;
            continue;
        }
            
        printf("value of b: %d\n", b);
        b++;
    
    } while( b < 20 );

    /* local variable definition */
    int c = 10;

    /* do loop execution */
    LOOP:do {
    
        if( c == 15) {
            /* skip the iteration */
            c = c + 1;
            goto LOOP;
        }
            
        printf("value of c: %d\n", c);
        c++;

    }while( c < 20 );

    return 0;
}