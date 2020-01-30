#ifndef POINT_H
#define POINT_H

#include <ostream>

class Point {
    public:
    Point(double x, double y, double z) : x(x), y(y), z(z) {};
    Point() : x(0), y(0), z(0) {};

    double magnitude() const;

    double x, y, z;
};

bool operator<(const Point& lhs, const Point& rhs);
std::ostream &operator<<(std::ostream &os, const Point &p);


#endif