#include <iostream>
#include "car.h"

using namespace elma;

void Car::start() {

    velocity = 0;
    
}

void Car::update() {

    if ( channel("Throttle").nonempty() ) {
        force = channel("Throttle").latest();
    }
    velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;
    channel("Velocity").send(velocity);
    std::cout << milli_time() << ","
                << velocity << " \n";

}