#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Sensor.h"
#include <Arduino.h>
class AnalogSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor
    int sensorValue = 0;
    int bias = 0;
    int max = 1023;
    
    int getLow(int torque);
    int getHigh(int torque);

public:
    // Constructor
    AnalogSensor(int id, int waitTime, int inPins, int bias, int max, int dataLength); 

    // Implement the pure virtual functions from the base class
    int readInputs() override;
    bool readyToCheck() override;
    int rescale(int data) override;
    int* buildData(int torque, int percent);
    int* buildData(int value);

    // Getters
    int getId();
    int getPins();
    int getWaitTime();
    int getDataLength();

    // Setters
    void setPin(int inPins);
    void setWaitTime(int inWait);
    void setId(int inId);
};

#endif // ANALOGSENSOR_H
