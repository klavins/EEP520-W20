#ifndef _EXTREMA_H
#define _EXTREMA_H

#include "elma/elma.h"

using namespace elma;

class Extrema : public Process {

    // This process keeps track of the minimum and maximum values
    // that it has seen on a channel called link.

    public:

    // The constructor calls the parent constructor, and initializes
    // a boolean, _no_data, which keeps track of whether this process
    // has seen any data.
    Extrema(std::string name) : Process(name), _no_data(true) {}

    void init() {}
    void start() {}
    void update();   // This method is implemented in extrema.cc
    void stop() {}

    // These getters return the min and max respectively,
    // or throw an error if no data has been observed. 
    double min() const;  
    double max() const;      

    private:

    bool _no_data;
    double _min, _max;

};  

#endif