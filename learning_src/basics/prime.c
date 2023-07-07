#include <stdio.h>
#include <time.h>
 
int main () 
{
    clock_t t;  
    int i, j, count;

    t = clock();
    
    for(i = 2; i<10000; i++) {

        for(j = 2; j <= (i/j); j++) 
        if(!(i%j)) break; // if factor found, not prime
        if(j > (i/j))
        {
            //printf("%d is prime\n", i);
            count++;
        }
    }
    printf("there are %d prime numbers from 0 to %d\n", count, i);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    
    printf("Runtime: %.4f\n", time_taken);

    //printf("Time taken: %.19f\n", time_taken);

    return 0;
}