#ifndef _DRIVER_H
#define _DRIVER_H

#include "elma/elma.h"

using namespace elma;

class Driver : public Process {

    public: 
    Driver(std::string name) : Process(name) {}
    void init();
    void start() {}
    void update();
    void stop() {}
    private:
    double desired_speed;

};

#endif