#ifndef CPOINT_H
#define CPOINT_H
struct Point; // forward declared for encapsulation
struct Point* Point__create(int x, int y); // equivalent to "new Point(x, y)"
void Point__destroy(Point* self); // equivalent to "delete point"
int Point__x(Point* self); // equivalent to "point->x()"
int Point__y(Point* self); // equivalent to "point->y()"
#endif