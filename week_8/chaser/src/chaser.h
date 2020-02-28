#ifndef __CHASER_AGENT__H
#define __CHASER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class ChaserController : public Process, public AgentInterface {

    public:
    ChaserController() : Process(), AgentInterface(), goal_x(0), goal_y(0) {}

    void init() {
        watch("goal_change", [this](Event e){
            goal_x = e.value()["x"];
            goal_y = e.value()["y"];
        });
        watch("agent_click", [this](Event e) {
            if ( e.value()["id"] == id() ) {
                std::cout << "I was clicked!!\n";
            }
        });
    }
    void start() {}
    void update() {
        move_toward(goal_x, goal_y, 100, 50);
    }
    void stop() {}

    double goal_x, goal_y;

};

class Chaser : public Agent {
    public:
    Chaser(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    ChaserController c;
};

DECLARE_INTERFACE(Chaser)

#endif