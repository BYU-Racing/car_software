#ifndef HORN_H
#define HORN_H

#include "Actuator.h"

class Horn : public Actuator {
private:
    // Additional attributes specific to Horn

public:
    // Constructor
    Horn();
    Horn(int* pins, int numPins);

    // Destructor

    // Override the writeToDisplay method
    void updateValue(const SensorData& data);

    // Additional methods for Horn
};

#endif // HORN_H
