#include "cpoint.h"

struct Point {
    int x;
    int y;
};

// Constructor (without allocation)
void Point__init(struct Point* self, int x, int y) {
    self->x = x;
    self->y = y;
}

// Allocation + initialization (equivalent to "new Point(x, y)")
struct Point* Point__create(int x, int y) {
    struct Point* result = (struct Point*) malloc(sizeof(struct Point));
    Point__init(result, x, y);
    return result;
}

// Destructor (without deallocation)
void Point__reset(struct Point* self) {
}

// Destructor + deallocation (equivalent to "delete point")
void Point__destroy(struct Point* point) {
  if (point) {
     Point__reset(point);
     free(point);
  }
}

// Equivalent to "Point::x()" in C++ version
int Point__x(struct Point* self) {
   return self->x;
}

// Equivalent to "Point::y()" in C++ version
int Point__y(struct Point* self) {
   return self->y;
}
