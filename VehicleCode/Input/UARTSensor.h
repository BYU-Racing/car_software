#ifndef UARTSENSOR_H
#define UARTSENSOR_H

#include "Sensor.h"


class UARTSensor : public Sensor {
private:
    // Additional attributes specific to UARTSensor

public:
    // Constructor
    UARTSensor(enum SensorID id, int freq, int prio);

    // TODO Destructor

    // Implement the pure virtual functions from the base class
    int* readInputs() override;
    bool readyToCheck() override;

    // Additional methods for UARTSensor
};

#endif // UARTSENSOR_H
