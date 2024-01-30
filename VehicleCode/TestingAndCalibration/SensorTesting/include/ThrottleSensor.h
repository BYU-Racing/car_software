#ifndef THROTTLESENSOR_H
#define THROTTLESENSOR_H

#include "Sensor.h"
#include <Arduino.h>
class ThrottleSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor
    int throttle1 = 0;
    int throttle2 = 0;
    int bias = 0;
    int max = 1023;
    
    int getLow(int torque);
    int getHigh(int torque);

public:
    // Constructor
    ThrottleSensor(int id, int waitTime, int inPins, int bias, int max, int dataLength); 

    // Implement the pure virtual functions from the base class
    int readInputs() override;
    bool readyToCheck() override;
    int rescale(int data) override;
    int* buildData(int torque, int percent);

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

#endif // THROTTLESENSOR_H
