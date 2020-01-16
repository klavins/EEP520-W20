#include "gtest/gtest.h"
#include "rpn.h"

namespace {

    TEST(HW2,RPN_BASICS) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_push(1.0);
        rpn_add();
        rpn_multiply();
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-1.5);
        ASSERT_EQ(rpn_error(), OK);
    }

}
