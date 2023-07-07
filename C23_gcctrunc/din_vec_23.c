#include <stdlib.h>
#include <stdio.h>

typedef struct vector {    
    size_t size;
    size_t capacity;
    double data[];
} vector;

void dump_vec(vector const * const);

bool vec_create(vector * vec[static 1], size_t cap) {
    if (*vec != nullptr)
        return false;
    
    constexpr size_t DEF_CAP = {16};
    cap = cap == 0 ? DEF_CAP : cap;

    *vec = malloc(sizeof(**vec) + sizeof(double[cap]));

    if (*vec != nullptr)
        **vec = (vector) {.capacity = cap};

    return *vec != nullptr;
}

int main(void) {
    vector * vec = nullptr;
    if (vec_create(&vec, 8)) { // can't accept nullptr in &vec
        printf("Created a vector\n\n");
        dump_vec(vec);
        free(vec);
    }
    return 0;
}

void dump_vec(vector const* const vec) {
    if (!vec) {
        printf("struct vector = nullptr\n");
    }
    else {
         
         printf("struct vector {\n"
            "   size_t size = %ld\n"
            "   size_t capacity = %ld\n"
            "   double * data = %p\n}\n"
            , vec->size
            , vec->capacity
            , (void *)vec->data);
    }
}

// -std=c2x -Wall -Wextra -pedantic O2 -fsanitize=address