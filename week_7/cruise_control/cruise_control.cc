#include <iostream>
#include "cruise_control.h"

using namespace elma;

void CruiseControl::init() {

    watch("desired speed", [this](Event& e) {
        desired_speed = e.value();
    });

}

void CruiseControl::update() {

    if ( channel("Velocity").nonempty() ) {
        speed = channel("Velocity").latest();
    }
    
    channel("Throttle").send(-KP*(speed - desired_speed));

}