// TODO: Add doc string


#ifndef SENSOR_H
#define SENSOR_H

#include "../SensorID.h"

class Sensor {
protected:
    // Instantiate attributes
    int* inputPins;
    int waitTime;
    int previousUpdateTime = 0;
    int sensorID;
    int priority;

public:
    // Constructor
    Sensor(int id, int freq, int prio, int* inputPins);

    // Destructor
    virtual ~Sensor();

    // Declare a pure virtual function
    // CHECK output: array of ints that ends with -1 as an end of array marker
    virtual int* readInputs() = 0;

    // Method to check if it's ready to read
    virtual bool readyToCheck() = 0;

    // CHECK add method to get id and priority
    int getId() const;
    int getPriority() const;
};

#endif // SENSOR_H
