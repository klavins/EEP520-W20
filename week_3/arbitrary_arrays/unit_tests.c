#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "arbitrary_array.h"
#include "gtest/gtest.h"

#define X 1.2345

typedef struct {
    double x, y, z;
} Point;

char * point_to_string ( void * p ) {
    Point * q = (Point *) p;
    char * str = (char *) calloc(40, sizeof(char));
    snprintf(str,40,"{%.1lf,%.1lf,%.1lf}", q->x, q->y, q->z);
    return str;
}

namespace {

    TEST(ArbitraryArray,Basics) {
        // Tests here
    } 

}