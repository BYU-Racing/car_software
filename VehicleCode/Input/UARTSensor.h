#ifndef UARTSENSOR_H
#define UARTSENSOR_H

#include "Sensor.h"

/*  UART INFO FOR TEENSY AND UART SENSORS

    PINS
    RX1     ->  0
    TX1     ->  1
    RX2     ->  7
    TX2     ->  8

    IMPORTANT DATA
    BAUD    ->  9600 (default)
    
*/

class UARTSensor : public Sensor {
private:
    // Additional attributes specific to UARTSensor

public:
    // Constructor
    UARTSensor(enum SensorID id, int freq, int prio);

    // Destructor

    // Implement the pure virtual functions from the base class
    int* readInputs() override;
    bool readyToCheck() override;

    // Additional methods for UARTSensor
};

#endif // UARTSENSOR_H
