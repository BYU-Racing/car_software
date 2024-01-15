#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Sensor.h"
#include <Arduino.h>
class AnalogSensor : public Sensor {
private:
    // Additional attributes specific to AnalogSensor
    int sensorValue = 0;
public:
    // Constructor
    AnalogSensor(int id, int freq, int inPins); // Id, Frequency, Priority

    // Implement the pure virtual functions from the base class
    int readInputs() override;
    bool readyToCheck() override;

    // Getters
    int getPins();
    int getWaitTime();

    // Setters
    void setPin(int inPins);
    void setWaitTime(int inWait);
    void setId(int inId);
};

#endif // ANALOGSENSOR_H
