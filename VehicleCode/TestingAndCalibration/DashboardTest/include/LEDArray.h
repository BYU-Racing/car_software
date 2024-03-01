#ifndef LEDARRAY_H
#define LEDARRAY_H

#include "Actuator.h"

class LEDArray : public Actuator {
private:
    // Additional attributes specific to LEDArray
    int currentState;
    int* ledPins; //Adjust to pinout for the LED
    int increment;

    int intervalTime;

    unsigned long lastUpdate;

public:
    // Constructor
    LEDArray();
    LEDArray(int* ledPinIn);
   
    // Destructor

    // Override the writeToDisplay method
    void updateValue(const SensorData& data);

    void displayLEDs(int value);

    // Additional methods for LEDArray
};

#endif // LEDARRAY_H
