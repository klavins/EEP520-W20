#ifndef __DIFF_DRIVE_AGENT__H
#define __DIFF_DRIVE_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BlockController : public Process, public AgentInterface {

    public:
    BlockController();

    void init() {}
    void start() {}
    void update();
    void stop() {}

};

class Block : public Agent {
    public:
    Block(json spec, World& world) : Agent(spec, world) {
        add_process(bc);
    }
    private:
    BlockController bc;

};

DECLARE_INTERFACE(Block)

#endif