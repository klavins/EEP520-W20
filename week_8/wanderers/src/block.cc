#include <iostream>
#include "block.h"

using namespace enviro;

BlockController::BlockController() : Process() {}

void BlockController::update() {
    agent->damp_movement();
}
