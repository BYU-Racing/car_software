// TODO: FIX THE CONSTRUCTOR
#include "AnalogSensor.h"
#include <Arduino.h>

//Constructor
AnalogSensor::AnalogSensor(int id, int freq, int inPins) {

    sensorID = id;
    waitTime = freq;
    previousUpdateTime = millis();
    inputPins[0] = inPins;
    inputPins[4] = -1;
    sensorValue = 0;
};

//readInputs
int AnalogSensor::readInputs() {

    //Update previous update time
    previousUpdateTime = millis();

    //Grab Sensor Value
    sensorValue = analogRead(inputPins[0]);

    //Return a pointer to the private value
    return sensorValue;
    
};


//readyToCheck
bool AnalogSensor::readyToCheck() {
    //millis gets arduino time
    return (waitTime <= int(millis() - previousUpdateTime));
};

int AnalogSensor::getPins() {
    return inputPins[0];
}

int AnalogSensor::getWaitTime() {
    return waitTime;
}

void AnalogSensor::setPin(int inPins) {
    inputPins[0] = inPins;
}
void AnalogSensor::setWaitTime(int inWait) {
    waitTime = inWait;
}
void AnalogSensor::setId(int inId) {

    sensorID = inId;
}