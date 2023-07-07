#ifndef EX1_H
#define EX1_H

typedef struct {
    char name[32];
    double speed;
    double fuel;
} car_t;

void car_construct(car_t* self, const char* name);
void car_destruct(car_t* self);
void car_accelerate(car_t* self);
void car_brake(car_t* self);
void car_refuel(car_t* self, double amount);

#endif
