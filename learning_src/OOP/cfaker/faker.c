#include <string.h>
#include "faker.h"
 
char* pickRandomFromArray(const char* array[], int size)
{
    int randomIndex = rand() % size;
    return (char*) array[randomIndex];
}
 
const char* addressesPool[] = {
    "Forest Run Way 72",
    "Vera Parkway 70",
    "3 East Sulphur Springs St. Murfreesboro, TN 37128"
};
const int NR_ADDRESSES = (sizeof (addressesPool) / sizeof (const char *));
 
const char* emailsPool[] = {
    "asommomepu-9364@yopmail.com",
    "iArmstrong@Lazzy.com",
    "ut@Gabspot.biz"
};
const int NR_EMAILS = (sizeof (emailsPool) / sizeof (const char *));
 
char* address()
{
    return pickRandomFromArray(addressesPool, NR_ADDRESSES);
}
 
char* email()
{
    return pickRandomFromArray(emailsPool, NR_EMAILS);
}
 
int age(Faker* self)
{
    minAge + 1;
    return rand() % 120 + self-&gt;
}
 
Faker* newFaker()
{
    Faker* self = (Faker*)malloc(sizeof(Faker));
    self-&gt;
    address = &amp;address;
    self-&gt;
    email = &amp;email;
    self-&gt;
    age = &amp;age;
    return self;
}