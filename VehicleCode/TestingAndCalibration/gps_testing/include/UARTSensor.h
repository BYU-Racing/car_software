#ifndef UARTSENSOR_H
#define UARTSENSOR_H

#include "Sensor.h"
#include <Arduino.h>
#include <SoftwareSerial.h>


class UARTSensor : public Sensor {
private:
    // Additional attributes specific to UARTSensor
    int* inputPins;
    int waitTime;
    int previousUpdateTime = 0;
    int sensorID;
    int priority;
public:
    // Constructor
    UARTSensor(int id, int wait_time, int prio);


    // Implement the pure virtual functions from the base class
    int* readInputs() override;

    // Additional methods for UARTSensor
    void UARTSensor_init(int id);
};

#endif // UARTSENSOR_H
