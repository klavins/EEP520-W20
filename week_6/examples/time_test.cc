#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace std::chrono; 
    using namespace elma;   

    TEST(TIME,HIGH_RES) {
       
        high_resolution_clock::time_point t = high_resolution_clock::now();
        std::cout << t.time_since_epoch().count() << " ns since 1970\n";
        typedef duration<double,std::ratio<3600*24*365,1>> years;
        auto y = years(t.time_since_epoch());
        std::cout << y.count() << " years since 1970\n";

    }

    void waste_time() {
        std::this_thread::sleep_for(10_ms);
    }

    TEST(TIME,EXEC_TIME) {

        high_resolution_clock::time_point t1, t2;
        t1 = high_resolution_clock::now();
        waste_time();
        t2 = high_resolution_clock::now();
        std::cout << "waste_time took " << (t2 - t1).count() << " ns\n";
        ASSERT_GE((t2-t1).count(), 10 * 1000 * 1000);

    }

}