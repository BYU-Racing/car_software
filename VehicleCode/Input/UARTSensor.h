#ifndef UARTSENSOR_H
#define UARTSENSOR_H

#include "Sensor.h"


class UARTSensor : public Sensor {
private:
    // Additional attributes specific to UARTSensor
    int* inputPins;
    int waitTime;
    int previousUpdateTime = 0;
    int sensorID;
    int priority;
public:
    // Constructor
    UARTSensor(enum SensorID id, int wait_time, int prio);

    // Destructor
    ~UARTSensor();

    // Implement the pure virtual functions from the base class
    int* readInputs() override;
    bool readyToCheck() override;

    // Additional methods for UARTSensor
    void UARTSensor_init(SensorID id);
};

#endif // UARTSENSOR_H
