// TODO: add doc string

#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Sensor.h"

class AnalogSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor

public:
    // Constructor
    AnalogSensor(int id, int freq, int prio, int* inPins); // Id, Frequency, Priority

    // Destructor
    ~AnalogSensor();

    // Implement the pure virtual functions from the base class
    int* readInputs();
    bool readyToCheck();

    // Additional methods for AnalogSensor
};

#endif // ANALOGSENSOR_H
