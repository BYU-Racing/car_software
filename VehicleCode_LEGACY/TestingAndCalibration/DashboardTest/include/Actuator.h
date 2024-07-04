#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "SensorData.h"

class Actuator {
private:
    // Instantiate attributes
    int* outputPins;

public:
    // Method to update the actuator value using sensor data
    virtual void updateValue(const SensorData& data) = 0;
};

#endif // ACTUATOR_H
