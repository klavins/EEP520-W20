#ifndef _MICROWAVE_H
#define _MICROWAVE_H

#include "elma/elma.h"

using namespace elma;

class DoorClosedOff : public State {
    public:
    DoorClosedOff() : State("Door closed off") {}
    void entry(const Event& e) {
        if ( e.name() == "power level set" ) {
            emit(Event("set power", e.value()));
        }
    }
    void during() {} 
    void exit(const Event& e) {
        if ( e.name() == "on button pressed" ) {
            emit(Event("on"));
        }        
    }
};

class DoorClosedOn : public State {
    public:
    DoorClosedOn() : State("Door closed on") {}
    void entry(const Event& e) {}
    void during() {} 
    void exit(const Event& e) {
        emit(Event("off"));
    }
};

class DoorOpen : public State {
    public:
    DoorOpen() : State("Door open") {}
    void entry(const Event& e) {
        if ( e.name() == "power level set" ) {
            emit(Event("set power", e.value()));
        }           
    }
    void during() {} 
    void exit(const Event& e) {}
};

class Microwave : public StateMachine {

    public:

    Microwave() : StateMachine() {
        set_initial(closed_off);
        add_transition("on button pressed", closed_off, closed_on);
        add_transition("door opened", closed_off, open);
        add_transition("power level set", closed_off, closed_off);
        add_transition("off button pressed", closed_on, closed_off);
        add_transition("door opened", closed_on, open);
        add_transition("door closed", open, closed_off);
        add_transition("power level set", open, open);        
    }

    private:

    DoorClosedOff closed_off;
    DoorClosedOn closed_on;
    DoorOpen open;      

};



#endif