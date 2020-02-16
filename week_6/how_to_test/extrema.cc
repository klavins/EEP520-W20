#include "extrema.h"

using namespace elma;

void Extrema::update() {

    // This method is called every time the process is updated. 
    // It checks for data on the channel, and assigns or reassigns
    // the _min and _max private variables as appropriate.

    if ( channel("link").nonempty() ) {
        double x = channel("link").latest();
        if ( _no_data ) {
            _no_data = false;
            _min = _max = x;
        } else {
            if ( x < _min ) {
                _min = x;
            }
            if ( x > _max ) {
                _max = x;
            }
        }
    }          
}

double Extrema::min() const {
    // returns the min value, or throws an error if there isn't one.
    if ( _no_data ) {
        throw std::runtime_error("Extrema process has no data");
    } else {
        return _min;
    }
}

double Extrema::max() const {
    // returns the max value, or throws an error if there isn't one.
    if ( _no_data ) {
        throw std::runtime_error("Extrema process has no data");
    } else {
        return _max;
    }
}    