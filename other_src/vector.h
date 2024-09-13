#pragma once
#include <stdlib.h>

typedef struct vector_t vector_t;

vector_t* vector_new();
void vector_create(vector_t* obj);
void vector_destroy(vector_t* obj);

int vector_size(vector_t* obj);
int vector_capacity(vector_t* obj);
int vector_at(vector_t* obj, const int index);

int* vector_begin(vector_t* obj);
int* vector_end(vector_t* obj);

void vector_push_back(vector_t* obj, const int element);
void vector_pop_back(vector_t* obj);
void vector_erase(vector_t* obj, int* first, int* last);