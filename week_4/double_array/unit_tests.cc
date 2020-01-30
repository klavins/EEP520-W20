#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "double_array.h"
#include "gtest/gtest.h"

namespace {

    TEST(DoubleArray, ConstructSetGet) {       
        DoubleArray a, b(0,1,0.1);
        auto c = new DoubleArray();
        a.set(4, 1);
        ASSERT_EQ(a.get(4), 1); 
        double x = 0;
        for ( int i=0; i<b.size(); i++ ) {
            ASSERT_EQ(b.get(i),x);
            x+=0.1;
        }
        delete c;
    }

    TEST(DoubleArray, Assignment) {
        DoubleArray a, b;  
        a.set(4, 1);
        b = a;
        ASSERT_EQ(a.get(4), 1);
        ASSERT_EQ(b.get(4), 1);                
    }    

    TEST(DoubleArray, Equality) {
        DoubleArray a(0,1,0.1), b(0,1,0.1), c(1,2,0.1);
        ASSERT_EQ(a, b);
        ASSERT_NE(a,c);                
    }       

    TEST(DoubleArray, CopyConstructor) {
        DoubleArray a;
        a.set(4, 1);        
        DoubleArray b(a);
        ASSERT_EQ(a.get(4), 1);
        ASSERT_EQ(b.get(4), 1);            
    }

    TEST(DoubleArray, Exceptions) {
        DoubleArray a;
        ASSERT_THROW(a.set(-1,0), std::range_error);
        ASSERT_THROW(a.get(-1), std::range_error);
        try {
            a.get(-1);
            ASSERT_EQ(0,1); // Should not reach this code
        } catch ( std::range_error e ) {
            ASSERT_STREQ(e.what(), "Negative index in array");
        }
    }

}