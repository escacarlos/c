#include <stdio.h>
#include <stdlib.h>
#include "car.h"

int main(int argc, char** argv) {

    struct car_t* car = car_new();

    car_ctor(car);

    printf("Engine temperature before starting the car: %f\n", car_get_engine_temperature(car));

    car_start(car);
    printf("Engine temperature after starting the car: %f\n", car_get_engine_temperature(car));

    car_stop(car);
    printf("Engine temperature after stopping the car: %f\n", car_get_engine_temperature(car));

    car_dtor(car);

    free(car);

    getchar();

    return 0;
}
