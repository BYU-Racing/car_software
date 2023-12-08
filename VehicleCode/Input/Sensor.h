// TODO Add doc string


#ifndef SENSOR_H
#define SENSOR_H

#include "../SensorID.h"

class Sensor {
protected:
    // Instantiate attributes
    int* inputPins;
    int waitTime;
    unsigned long previousUpdateTime = 0;
    int sensorID;
    int priority;

public:
    // CHECK: deleted  the constructer and destructor declaration bc we never defined it

    // Declare a pure virtual function
    virtual int* readInputs() = 0;

    // Method to check if it's ready to read
    bool readyToCheck(){
        // CHECK: @dallin I defined this in this file because it will 
        // be the same in all of the sensors so it would be redundant 
        // to define it in each individually
        return (waitTime <= millis() - previousUpdateTime);
    }
};

#endif // SENSOR_H
