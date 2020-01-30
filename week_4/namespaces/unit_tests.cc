#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "gtest/gtest.h"

namespace my_library {

    typedef struct {
        double x, y;
    } Point;

    int mag(Point &p) {
        return sqrt(p.x*p.x + p.y*p.y);
    }    

}

namespace {

    TEST(Examples, MyLibrary) {
        my_library::Point p = { x: 3, y: 4};
        ASSERT_NEAR(my_library::mag(p), 5, 0.00001);
    }

    TEST(Examples, Using) {
        using namespace my_library;
        Point p = { x: 3, y: 4};
        ASSERT_NEAR(mag(p), 5, 0.00001);
    }    
    
}
