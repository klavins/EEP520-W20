#include <iostream>
#include "driver.h"

using namespace elma;

void Driver::init() {
    desired_speed = 50;
}

void Driver::update() {
    if ( desired_speed == 50 ) {
        desired_speed = 60;
    } else {
        desired_speed = 50;
    }
    emit(Event("desired speed", desired_speed));
}