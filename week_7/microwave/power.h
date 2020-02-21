#ifndef _POWER_H
#define _POWER_H

#include "elma/elma.h"

using namespace elma;

class Power : public Process {

    public:
    Power() : Process("power") {}
    void init() {
        watch("on", [this](Event& e) {
            running = true;
        });
        watch("off", [this](Event &e) {
            running = false;
        });
        watch("set power", [this](Event& e) {
            power_level = e.value();
        });
    }
    void start() {
        running = false;
        power_level = 0;
    }
    void update() {}
    void stop() {}

    bool running;
    double power_level;

};

#endif