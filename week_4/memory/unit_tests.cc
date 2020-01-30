#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "gtest/gtest.h"

namespace {

    TEST(Examples, Allocation) {
        int * x = new int;
        double * p = new double[10];
        delete x;
        delete[] p;
    }

}
