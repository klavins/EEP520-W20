#include "gtest/gtest.h"
#include "elma/elma.h"
#include "power.h"
#include "microwave.h"

using namespace std::chrono;
using namespace elma;

namespace {
   
    TEST(Microwave, Safety) {

        Manager m;
        Power power;      
        Microwave microwave;

        m.schedule(power, 10_ms)
         .schedule(microwave, 10_ms)
         .init();

        m.start();
        m.emit(Event("on button pressed"));
        ASSERT_EQ(true, power.running);

        m.start();
        m.emit(Event("door opened"));    
        m.emit(Event("on button pressed"));
        ASSERT_EQ(false, power.running);

        // ETC

    }

}
