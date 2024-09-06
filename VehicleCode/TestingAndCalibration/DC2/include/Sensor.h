// TODO: Add doc string


#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// CHECK moving this here should save a small amount of space
#define ARRAY_SIZE 4

class Sensor {
protected:
    // Instantiate attributes
    int inputPins[ARRAY_SIZE];
    int waitTime;
    unsigned long previousUpdateTime = 0;
    int sensorID;
    int dataLength;
    bool critical;

public:

    //virtual ~Sensor();
    virtual int getId() = 0;
    virtual int getDataLength() = 0;

    // Declare a pure virtual function
    virtual int readInputs() = 0;

    // Method to check if it's ready to read
    bool readyToCheck(){
        return (waitTime <= int(millis() - previousUpdateTime));
    }

    // Method to transform data
    virtual int rescale(int data) = 0;
    virtual int* buildData(int value) = 0;
    virtual int* buildError() = 0;
    virtual bool getCritical();
    virtual bool plugTest();
};

#endif // SENSOR_H
