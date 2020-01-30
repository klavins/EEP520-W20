#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "gtest/gtest.h"

namespace {

    double invert(int x, int y) {
        if ( x == 0 ) {
            throw std::invalid_argument("First argument cannot be zero");
        } else {
            return y/x;
        }
    }    

    TEST(Examples, NormalBehavior) {
        ASSERT_NEAR(invert(1,2), 2, 0.00001);
    }

    TEST(Examples, ExceptionalBehavior) {
        try {
            invert(0,1);
            ASSERT_EQ(true,false);
        } catch (std::invalid_argument e ) {
            ASSERT_STREQ(e.what(), "First argument cannot be zero");
        }
    }    
    
}
