#include "gtest/gtest.h"
#include "example.h"

namespace {

    int sum(int n) {
        int s = 0;
        for (int i=0; i<n; i++) {
            s = s + i;
        }
        return s;
    }    

    TEST(Example,TestAddOne) {
        ASSERT_EQ(add_one(0),1);
    }

    TEST(WEEK2, Types) {
        ASSERT_EQ(sum(10),45);
    }

}
