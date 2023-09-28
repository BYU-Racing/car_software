#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "../Input/SensorData.h"

class Actuator {
private:
    // Instantiate attributes
    int* outputPins;
    int value;

public:
    // Constructor
    Actuator(int* pins, int numPins);

    // Destructor
    virtual ~Actuator();

    // Declare a pure virtual function
    virtual void writeToDisplay() = 0;

    // Method to update the actuator value using sensor data
    virtual void updateValue(const SensorData& data) = 0;
};

#endif // ACTUATOR_H
