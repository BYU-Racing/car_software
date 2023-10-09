#include "Servo.h"
#include "SensorData.h"

//Constructor 
Servo::Servo(int* pins, int numPins):Actuator(int *pins, int numPins) {
    this->pins = pins;
    this->numPins = numPins;
};

// Update the value given new data
void updateValue(const SensorData& data) {
    dataValue = data.getData();
}