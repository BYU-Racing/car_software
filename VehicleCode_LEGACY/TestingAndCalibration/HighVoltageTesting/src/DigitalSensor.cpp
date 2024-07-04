// #include "DigitalSensor.h"
// #include <Arduino.h>

// DigitalSensor::DigitalSensor(int id, int freq, int prio, int inPins) {
//     sensorID = id;
//     waitTime = freq;
//     previousUpdateTime = 0;
//     inputPins[4] = -1;
//     inputPins[0] = inPins;
//     priority = prio;

//     //Add code so that  -1 is added to the end of the input pins array
// } 

// int DigitalSensor::readInputs() {

//     previousUpdateTime = millis();

//     sensorValue = digitalRead(inputPins[0]);

//     return sensorValue;
// }

// //destructor code ??

// //bool Ready to check

// bool DigitalSensor::readyToCheck() {
//     return (waitTime <= int(millis() - previousUpdateTime));
// }

// int DigitalSensor::getPins() {
//     return inputPins[0];
// }

// int DigitalSensor::getWaitTime() {
//     return waitTime;
// }

// void DigitalSensor::setPin(int pin) {
//     inputPins[0] = pin;
// }

// void DigitalSensor::setWaitTime(int inWait) {
//     waitTime = inWait;
// }

// void DigitalSensor::setId(int inId) {
//     sensorID = inId;
// }

