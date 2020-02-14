#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;
    using namespace std::chrono;
    using std::vector;

    class Car : public Process {
        public:

        Car(std::string name) : Process(name) {}

        void init() {}

        void start() {
            velocity = 0;
        }

        void update() {
            if ( channel("Throttle").nonempty() ) {
                force = channel("Throttle").latest();
            }
            velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;
            channel("Velocity").send(velocity);
            std::cout << milli_time() << ","
                    << velocity << " \n";
        }

        void stop() {}

        private:
        double velocity;
        double force;
        const double k = 0.02;
        const double m = 1000;

    };  

    class CruiseControl : public Process {

        public:

        CruiseControl(std::string name) : Process(name) {}

        void init() {
            desired_speed = 60;
        }

        void start() {}

        void update() {
            if ( channel("Velocity").nonempty() ) {
                speed = channel("Velocity").latest();
            }
            channel("Throttle").send(-KP*(speed - desired_speed));
        }

        void stop() {}

        private:
        double speed = 0;
        double desired_speed = 0.0;
        const double KP = 314.15;
        vector<double> _v;
    };

    TEST(ELMA,CRUSE_CONTROL) {

        Manager m;

        Car car("Car");
        CruiseControl cc("Control");
        Channel throttle("Throttle");
        Channel velocity("Velocity");

        m.schedule(car, 100_ms)
         .schedule(cc, 100_ms)
         .add_channel(throttle)
         .add_channel(velocity)
         .init()
         .run(10_s);

    }    

}

