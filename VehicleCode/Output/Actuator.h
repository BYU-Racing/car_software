#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "../Input/SensorData.h"

class Actuator {
private:
    // Instantiate attributes
    int* outputPins;

public:
    // Constructor
    Actuator(int* pins, int numPins);

    // Destructor
    virtual ~Actuator();

    // Method to update the actuator value using sensor data
    virtual void updateValue(const SensorData& data) = 0;
};

#endif // ACTUATOR_H
