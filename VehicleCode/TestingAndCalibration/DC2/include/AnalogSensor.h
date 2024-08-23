#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Sensor.h"
#include <Arduino.h>

class AnalogSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor
    int sensorValue = 0;
    bool isCritical;
    // int bias = 0;
    // int max = 1023;

public:
    // Constructor
    AnalogSensor(int id, int waitTime, int inPin, bool isCritical); 

    // Implement the pure virtual functions from the base class
    int readInputs() override;
    bool readyToCheck();
    int rescale(int data) override;
    int* buildData(int value) override;
    int* buildError() override;
    bool getCritical() override;
    bool plugTest() override;

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
