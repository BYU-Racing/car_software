// TODO: all
#include "AnalogSensor.h"

//Constructor (Broken)
AnalogSensor::AnalogSensor(int id, int freq, int prio, int* inPins):Sensor(id, freq, prio, inPins) {
    int sensorID = id;
    int waitTime = freq;
    int priority = prio;
    int* inputPins = inPins;
};

//readInputs
int* AnalogSensor::readInputs() {

    //Update previous update time
    
    //Pull the data from the pin and return the pointer to it

    
};


//readyToCheck
bool AnalogSensor::readyToCheck() {
    //return (waitTime <= millis() - previousUpdateTime);
    // millis() grabs time from boot from Arduino
    return false;
    
};