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


    //Additional Methods for the updateValue
    void displayLEDsPerc(int value);
    void displayLEDsTemp(int value);


public:
    // Constructor
    LEDArray();
    LEDArray(int* ledPinIn);
   
    // Destructor
    //TODO: TALK TO DALLIN ABOUT THIS (SEE: ACTUATOR.H)

    // Override the writeToDisplay method
    void updateValue(const SensorData& data);
};

#endif // LEDARRAY_H
