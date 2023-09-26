#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "../Input/SensorData.h"  // Include the header for the SensorData class

class Actuator {
private:
    int* outputPins;   // Array of output pins
    int value;         // Current value

public:
    // Constructor
    Actuator(int* pins, int numPins);

    // Destructor
    virtual ~Actuator();  // Make the destructor virtual

    // Declare a pure virtual function
    virtual void writeToDisplay() = 0;

    // Method to update the actuator value using sensor data
    virtual void updateValue(const SensorData& data) = 0;
};

#endif // ACTUATOR_H
