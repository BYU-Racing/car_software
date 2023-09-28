#ifndef LEDARRAY_H
#define LEDARRAY_H

#include "Actuator.h"

class LEDArray : public Actuator {
private:
    // Additional attributes specific to LEDArray

public:
    // Constructor
    LEDArray(int* pins, int numPins);

    // Destructor

    // Override the writeToDisplay method
    void writeToDisplay() override;

    // Additional methods for LEDArray
};

#endif // LEDARRAY_H
