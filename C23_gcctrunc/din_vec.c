#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
    double * data;
    size_t size;
    size_t capacity;
} vector;

void dump_vec(vector const * const vec);

#define DEF_CAP (16)

int vec_create(vector ** vec, size_t cap) {
    if (*vec != NULL)
        return -1;
    
    *vec = (vector *)malloc(sizeof(**vec));
    if (*vec == NULL)
        return -1;

    cap = cap == 0 ? DEF_CAP : cap;

    (*vec)->data = (double *)malloc(cap * sizeof(double));

    if ((*vec)->data == NULL) {
        free(*vec);
        *vec = NULL;
        return -1;
    }

    (*vec)->capacity = cap;
    (*vec)->size = 0;
    return 1;
}

int main(void) {
    vector * vec = NULL;
    if (vec_create(&vec, 8)) {
        printf("Created a vector\n\n");
        dump_vec(vec);
        free(vec->data);
        free(vec);
    }
    return 0;
}

void dump_vec(vector const* const vec) {
    if (!vec) {
        printf("struct vector = NULL\n");
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