#ifndef LEDARRAY_H
#define LEDARRAY_H

#include "Actuator.h"  // Include the header for the Actuator class

class LEDArray : public Actuator {
private:
    // Additional attributes specific to LEDArray, if any

public:
    // Constructor
    LEDArray(int* pins, int numPins);

    // Destructor (if needed)

    // Override the writeToDisplay method
    void writeToDisplay() override;

    // Additional methods for LEDArray, if any
};

#endif // LEDARRAY_H
