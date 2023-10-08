#ifndef SCREEN_H
#define SCREEN_H

#include "Actuator.h"

class Screen : public Actuator {
private:
    // Additional attributes specific to Screen

public:
    // Constructor
    Screen();
    Screen(int* pins, int numPins);

    // Destructor

    // Override the writeToDisplay method
    void updateValue(const SensorData& data);

    // Additional methods for Screen
};

#endif // SCREEN_H
