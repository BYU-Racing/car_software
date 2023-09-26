#ifndef SCREEN_H
#define SCREEN_H

#include "Actuator.h"  // Include the header for the Actuator class

class Screen : public Actuator {
private:
    // Additional attributes specific to Screen, if any

public:
    // Constructor
    Screen(int* pins, int numPins);

    // Destructor (if needed)

    // Override the writeToDisplay method
    void writeToDisplay() override;

    // Additional methods for Screen, if any
};

#endif // SCREEN_H
