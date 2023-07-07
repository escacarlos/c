#include <stdio.h>
 
int main () {

    int n[ 10 ]; /* n is an array of 10 integers */
    int i,j;
    
    /* initialize elements of array n to 0 */         
    for ( i = 0; i < 10; i++ ) {
        n[ i ] = i + 100; /* set element at location i to i + 100 */
    }

    /* output each array element's value */
    for (j = 0; j < 10; j++ ) {
        printf("Element[%d] = %d\n", j, n[j] );
    }

    /* an array with 5 rows and 2 columns*/
    int a[5][2] = { {0,0}, {1,2}, {2,4}, {3,6},{4,8}};
    int i1, j1;
    
    /* output each array element's value */
    for ( i1 = 0; i1 < 5; i1++ ) {

        for ( j1 = 0; j1 < 2; j1++ ) {
            printf("a[%d][%d] = %d\n", i1,j1, a[i1][j1] );
        }
    }
    
    return 0;
}

    /*
    int a[3][4] = {  
    {0, 1, 2, 3} ,     initializers for row indexed by 0 
    {4, 5, 6, 7} ,     initializers for row indexed by 1 
    {8, 9, 10, 11}     initializers for row indexed by 2 
        }; 
        
        Is equal to initializate like this: 
        
        int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};

    */
