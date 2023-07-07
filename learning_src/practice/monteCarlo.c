#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double marblesSimulation (int);

int main() {
    clock_t t;
    t = clock();
    printf("%f", marblesSimulation(10000));
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("\nTime taken = %1.3f", time_taken);
    
    clock_t t1;
    t1 = clock();
    printf("\n%f", marblesSimulation(100000));
    t1 = clock() - t1;
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    printf("\nTime taken = %1.3f", time_taken1);
    
    clock_t t2;
    t2 = clock();
    printf("\n%f", marblesSimulation(1000000));
    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
    printf("\nTime taken = %1.3f", time_taken2);
    
    clock_t t3;
    t3 = clock();
    printf("\n%f", marblesSimulation(10000000));
    t3 = clock() - t3;
    double time_taken3 = ((double)t3)/CLOCKS_PER_SEC; // in seconds
    printf("\nTime taken = %1.3f", time_taken3);
    
    clock_t t4;
    t4 = clock();
    printf("\n%f", marblesSimulation(100000000));
    t4 = clock() - t4;
    double time_taken4 = ((double)t4)/CLOCKS_PER_SEC; // in seconds
    printf("\nTime taken = %1.3f", time_taken4);
    return 0;
}

double marblesSimulation (int attemps) {
    double success = 0.0;
    time_t t;
    int totalAttemps = attemps;
    srand((int) time(&t));
    char* draw = (char*) malloc(3*sizeof(int));
    while(attemps>0) {
        char bowl[6] = {'B', 'B', 'B', 'W', 'W', 'W'};
        int n = 6;
        for(int i=0; i<3; i++) {
            /* set the seed */          
            int r = rand()%n;
            //printf("%d, ", r);
            draw[i]=bowl[r];
            bowl[r]=bowl[n-1];
            n--;
        }
        if(draw[0] == 'B' && draw[1] == 'B' && draw[2] == 'B') {
            success++;
            attemps--;
        } else if(draw[0] == 'W' && draw[1] == 'W' && draw[2] == 'W') {
			success++;
			attemps--;
        }else attemps--;
    }
    free(draw);
    return success/totalAttemps;
}