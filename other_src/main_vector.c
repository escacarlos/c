#include "vector.h"
#include <stdio.h>

int main() {
  vector_t* my_vector = vector_new();
  vector_create(my_vector);

  printf("Vector Size: %d\n", vector_size(my_vector));
  printf("Vector Capacity: %d\n", vector_capacity(my_vector));

  vector_push_back(my_vector, 42);

  printf("Vector Size: %d\n", vector_size(my_vector));
  printf("Vector Capacity: %d\n", vector_capacity(my_vector));

  vector_push_back(my_vector, 55);
  vector_push_back(my_vector, 34);
  vector_push_back(my_vector, 67);
  vector_push_back(my_vector, 70);

  printf("Vector Size: %d\n", vector_size(my_vector));
  printf("Vector Capacity: %d\n", vector_capacity(my_vector));

  printf("Vector Element begin(): %d\n", *vector_begin(my_vector));
  /* printf("Vector Element end(): %d\n", *vector_end(my_vector));  /* NEVER! do this */

  for(int i = 0; i<5; i++) {
    printf("Element at %d: %d\n", i, vector_at(my_vector, i));
  }

  for(int* it=vector_begin(my_vector); it != vector_end(my_vector); it++) {
    printf("Element iterated: %d\n", *it);
  }

  printf("Vector Size before Pop: %d\n", vector_size(my_vector));
  printf("Vector Capacity before Pop: %d\n", vector_capacity(my_vector));
    
  vector_pop_back(my_vector);

  for(int i = 0; i<4; i++) {
      printf("Element at %d: %d\n", i, vector_at(my_vector, i));
  }

  printf("Vector Size after Pop: %d\n", vector_size(my_vector));
  printf("Vector Capacity after Pop: %d\n", vector_capacity(my_vector));

  /* Remove first element only */
  vector_erase(my_vector, vector_begin(my_vector), NULL); 
  /* Remove all Elements from second to last */
  vector_erase(my_vector, vector_begin(my_vector) + 1, vector_end(my_vector)); 

  for(int i = 0; i<vector_size(my_vector); i++) {
      printf("Element at %d: %d\n", i, vector_at(my_vector, i));
  }

  printf("Vector Size after Erase: %d\n", vector_size(my_vector));
  printf("Vector Capacity after Erase: %d\n", vector_capacity(my_vector));
  
  vector_destroy(my_vector);
  return 0;
}