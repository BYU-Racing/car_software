#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

#include "Sensor.h"
#include "../SensorID.h"

class DigitalSensor : public Sensor {
private:
    // Instantiate attributes
    int* inputPins;
    int waitTime;
    unsigned long previousUpdateTime = 0;
    int sensorID;
    int priority;
    int* sensorValue;

public:
    // Constructor
    DigitalSensor(int id, int freq, int prio, int* inputPins);

    // Destructor
    ~DigitalSensor();

    // Implement the pure virtual functions from the base class
    int* readInputs() override;
    bool readyToCheck() override;

    // CHECK add method to get id and priority
    int getId() const;
    int getPriority() const;
};

#endif // DIGITALSENSOR_H
