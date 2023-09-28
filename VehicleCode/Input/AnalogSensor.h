#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Sensor.h"

class AnalogSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor

public:
    // Constructor
    AnalogSensor(enum SensorID id, int freq, int prio);

    // Destructor

    // Implement the pure virtual functions from the base class
    int* readInputs() override;
    bool readyToCheck() override;

    // Additional methods for AnalogSensor
};

#endif // ANALOGSENSOR_H
