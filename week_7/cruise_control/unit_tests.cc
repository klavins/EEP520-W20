#include "gtest/gtest.h"
#include "car.h"
#include "driver.h"
#include "cruise_control.h"

namespace {
   
    TEST(Car,ItWorks) {
        Manager m;
        Car car("Car");
        CruiseControl cc("Control");
        Driver driver("Steve");
        Channel throttle("Throttle");
        Channel velocity("Velocity");

        m.schedule(car, 100_ms)
        .schedule(cc, 100_ms)
        .schedule(driver, 5_s)
        .add_channel(throttle)
        .add_channel(velocity)
        .init()
        .run(40_s);

    }

}