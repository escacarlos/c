#include <string.h>

#include "ex1.h"

void car_construct(car_t* self, const char* name) {
    strcpy(self->name, name);
    self->speed = 0.0;
    self->fuel = 0.0;
}

void car_destruct(car_t* self) {
}

void car_accelerate(car_t* self) {
    self->speed += 0.05;
    self->fuel -= 1.0;
    if(self->fuel < 0.0) {
	self->fuel = 0.0;
    }
}

void car_brake(car_t* self) {
    self->speed -= 0.07;
    if (self->speed < 0.0) {
	self->speed = 0.0;
    }
    self->fuel -= 2.0;
    if (self->fuel < 0.0) {
	self->speed = 0.0;
    }
}

void car_refuel(car_t* self, double amount) {
    self->fuel = amount;
}
