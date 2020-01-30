#include <math.h>
#include <ostream>
#include "point.h"

double Point::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

bool operator<(const Point& lhs, const Point& rhs) {

    double m1 = lhs.magnitude(), 
           m2 = rhs.magnitude();

    if ( m1 < m2 ) {
        return 1;
    } else if ( m1 > m2 ) {
        return -1;
    } else {
        return 0;
    }

} 

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << '{' << p.x << "," << p.y << "," << p.z << '}';
    return os;
}
