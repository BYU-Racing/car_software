#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

#include "Sensor.h"

class DigitalSensor : public Sensor {
private:
    // Additional attributes specific to DigitalSensor

public:
    // Constructor
    DigitalSensor(enum SensorID id, int freq, int prio);

    // Destructor

    // Implement the pure virtual functions from the base class
    int* readInputs() override;
    bool readyToCheck() override;

    // Additional methods for DigitalSensor
};

#endif // DIGITALSENSOR_H
