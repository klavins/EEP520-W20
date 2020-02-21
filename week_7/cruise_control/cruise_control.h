#ifndef _CRUISE_H
#define _CRUISE_H

#include "elma/elma.h"

using namespace elma;

class CruiseControl : public Process {

    public:

    CruiseControl(std::string name) : Process(name) {}
    void init();
    void start() {}
    void update();
    void stop() {}

    private:
    
    double speed = 0;
    double desired_speed = 0.0;
    const double KP = 314.15;
                 vector<double> _v;

};

#endif