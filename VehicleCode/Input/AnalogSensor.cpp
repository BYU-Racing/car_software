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

    
};


//readyToCheck
bool AnalogSensor::readyToCheck() {
    //return (waitTime <= currentTime - previousUpdateTime);
    return false;
    
};