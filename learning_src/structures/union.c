#include <stdio.h>
#include <string.h>
 
union Data {
   int i;
   float f;
   char str[20];
};
 
int main( ) {

    union Data data;        

    printf( "Memory size occupied by data : %d\n", sizeof(data));

    data.i = 10;
    data.f = 220.5;
    strcpy( data.str, "C Programming");

    printf( "data.i : %d\n", data.i);
    printf( "data.f : %f\n", data.f);
    printf( "data.str : %s\n", data.str);

    /* Here, we can see that the values of i and f members of union 
    got corrupted because the final value assigned to the variable 
    has occupied the memory location and this is the reason that the
    value of str member is getting printed very well.

    Now let's look into the same example once again where we will use
    one variable at a time which is the main purpose of having unions − */
    
    data.i = 10;
    printf( "data.i : %d\n", data.i);
    
    data.f = 220.5;
    printf( "data.f : %f\n", data.f);
    
    strcpy( data.str, "C Programming");
    printf( "data.str : %s\n", data.str);

    return 0;
}

/* Defining a Union

union [union tag] {
   member definition;
   member definition;
   ...
   member definition;
} [one or more union variables]; 

union Data {
   int i;
   float f;
   char str[20];
} data; */