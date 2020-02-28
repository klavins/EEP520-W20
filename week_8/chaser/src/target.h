#ifndef __TARGET_AGENT__H
#define __TARGET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class TargetController : public Process, public AgentInterface {

    public:
    TargetController() : Process(), AgentInterface() {}

    void init() {
        watch("screen_click", [this](Event e) {
            teleport(e.value()["x"], e.value()["y"], 0);
            emit(Event("goal_change", { 
                { "x", e.value()["x"] }, 
                { "y", e.value()["y"] } 
            }));
        });
    }

    void start() {}
    void update(){
        damp_movement();
    }
    void stop() {}

};

class Target : public Agent {
    public:
    Target(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    TargetController c;
};

DECLARE_INTERFACE(Target)

#endif