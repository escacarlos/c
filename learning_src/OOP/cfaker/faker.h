#ifndef faker_H_
#define faker_H_
 
typedef struct Faker; //forward declaration to allow self referencing in the struct declaration
struct Faker {
    int minAge;
    char* (*address) ();
    char* (*email) ();
    int age(Faker* self);
};
 
Faker* newFaker(int minAge);
 
#endif
