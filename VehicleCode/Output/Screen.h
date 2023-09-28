#ifndef SCREEN_H
#define SCREEN_H

#include "Actuator.h"

class Screen : public Actuator {
private:
    // Additional attributes specific to Screen

public:
    // Constructor
    Screen(int* pins, int numPins);

    // Destructor

    // Override the writeToDisplay method
    void writeToDisplay() override;

    // Additional methods for Screen
};

#endif // SCREEN_H
