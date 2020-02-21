#ifndef _CAR_H
#define _CAR_H

#include "elma/elma.h"

using namespace elma;

class Car : public Process {

    public:

    Car(std::string name) : Process(name) {}
    void init() {}
    void start();
    void update();
    void stop() {}

    private:
    
    double velocity;
    double force;
    const double k = 0.02;
    const double m = 1000;

};  

#endif