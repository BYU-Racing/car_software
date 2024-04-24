#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Sensor.h"
#include <Arduino.h>

class AnalogSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor
    // Currently None are needed

public:
    // Constructor
    AnalogSensor(int id, int waitTime, int inPin); 

    // Implement the pure virtual functions from the base class
    int readInputs() override;
    bool readyToCheck() override;
    int rescale(int data) override;
    int* buildData(int value) override;
    int* buildError() override;

    // Getters
    int getId();
    int getPins();
    int getWaitTime();
    int getDataLength();

    // Setters
    void setPin(int inPin, int index=0);
    void setWaitTime(int inWait);
    void setId(int inId);
};

#endif // ANALOGSENSOR_H
