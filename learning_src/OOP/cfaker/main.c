#include <stdio.h>
#include "faker.h"
 
int main()
{
    Faker* faker = newFaker(18);
    printf("Random age %d\n", faker->age(faker));
    printf("Random address: %s\n", faker->address());
    printf("Random email: %s\n", faker->email());
}