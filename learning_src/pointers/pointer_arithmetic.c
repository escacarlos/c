// Incrementing a Pointer

#include <stdio.h>

const int MAX = 3;

int main () {

    int  var[] = {10, 100, 200};
    int  i, j, *ptr, *ptrD,*ptrC;

    /* let us have array address in pointer */
    ptr = var;
    ptrC = var;
    ptrD = &var[MAX-1];
        
    for ( i = 0; i < MAX; i++) {

        printf("Address of var[%d] = %x\n", i, ptr );
        printf("Value of var[%d] = %d\n", i, *ptr );

        /* move to the next location */
        ptr++;
    }
    j = 0;
    while ( ptrC <= &var[MAX - 1] ) {

      printf("Address of var[%d] = %x\n", j, ptrC );
      printf("Value of var[%d] = %d\n", j, *ptrC );

      /* point to the next location */
      ptrC++;
      j++;
    }
    for ( i = MAX; i > 0; i--) {

        printf("Address of var[%d] = %x\n", i-1, ptrD );
        printf("Value of var[%d] = %d\n", i-1, *ptrD );

        /* move to the previous location */
        ptrD--;
    }
	
   return 0;
}