// TODO: Add doc string


#ifndef SENSOR_H
#define SENSOR_H

#include "SensorID.h"

class Sensor {
protected:
    // Instantiate attributes
    static const int ARRAY_SIZE = 5; // Size = pins + 1 for end of array marker
    int inputPins[ARRAY_SIZE];
    int waitTime;
    unsigned long previousUpdateTime = 0;
    int sensorID;
    int priority;

public:

    // Destructor
    //virtual ~Sensor();

    // Declare a pure virtual function
    // TODO output: array of ints that ends with -1 as an end of array marker
        // ^^ This for the inputPins Array?
    virtual int readInputs() = 0;

    // Method to check if it's ready to read
    virtual bool readyToCheck() = 0;
};

#endif // SENSOR_H
