#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person
{
  char *firstname;
  char *lastname;
  int age;

  // Public Interface
  int (*get_age)(const struct Person *self);
  char *(*get_firstname)(const struct Person *self);
  char *(*get_lastname)(const struct Person *self);
  void (*set_age)(struct Person *self, const int new_age);
  void (*set_firstname)(struct Person *self, const char *new_firstname);
  void (*set_lastname)(struct Person *self, const char *new_lastname);
  void (*print)(const struct Person *self);
  void (*del)(struct Person *self);
} Person;

int age_(const Person *self) { return self->age; }
char *firstname_(const Person *self) { return self->firstname; }
char *lastname_(const Person *self) { return self->lastname; }
void s_age_(Person *self, const int new_age)
{
  self->age = new_age;
}
void s_firstname_(Person *self, const char *new_firstname)
{
  free(self->firstname);
  self->firstname = strdup(new_firstname);
}
void s_lastname_(Person *self, const char *new_lastname)
{
  free(self->lastname);
  self->lastname = strdup(new_lastname);
}
void print_(const Person *self)
{
  printf("Object Person@%p\nfull name: %s %s\nage: %d",
         (void *)self, self->get_firstname(self), self->get_lastname(self), self->get_age(self));
}
void del_(Person *self)
{
  free(self->firstname);
  free(self->lastname);
  free((void *)self);
}

Person *Person_new()
{
  Person *p = (Person *)malloc(sizeof(*p));
  if (!p)
  {
    perror("Person_new: Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  p->firstname = NULL;
  p->lastname = NULL;
  p->age = 0;

  p->get_age = &age_;
  p->get_firstname = &firstname_;
  p->get_lastname = &lastname_;
  p->set_age = &s_age_;
  p->set_firstname = &s_firstname_;
  p->set_lastname = &s_lastname_;
  p->print = &print_;
  p->del = &del_;
  return p;
}

int main(void)
{
  printf("%s", "Hello World\n");
  Person *p = Person_new();
  p->set_firstname(p, "John");
  p->set_lastname(p, "Doe");
  p->set_age(p, 30);

  p->print(p);
  p->del(p);
  return 0;
}
