// TODO: Add doc string


#ifndef SENSOR_H
#define SENSOR_H

#include "SensorID.h"

class Sensor {
protected:
    // Instantiate attributes
    int* inputPins;
    int waitTime;
    unsigned long previousUpdateTime = 0;
    int sensorID;
    int priority;

public:
    // CHECK: deleted constructor since we never use it

    // Declare a pure virtual function
    // TODO output: array of ints that ends with -1 as an end of array marker
    virtual int* readInputs() = 0;

    // Method to check if it's ready to read
    bool readyToCheck(){
        // CHECK: defined this function here because it should be the same for all children classes
        return (waitTime <= int(millis()) - previousUpdateTime);
    }

    // add method to get id and priority
    int getId() const;
    int getPriority() const;
};

#endif // SENSOR_H
