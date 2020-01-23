#include "gtest/gtest.h"
#include "example.h"

namespace { 

    TEST(Example,TestAddOne) {
        ASSERT_EQ(add_one(0),1);
    }

}
