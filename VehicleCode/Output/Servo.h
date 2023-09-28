#ifndef SERVO_H
#define SERVO_H

#include "Actuator.h"

class Servo : public Actuator {
private:
    // Additional attributes specific to Servo

public:
    // Constructor
    Servo(int* pins, int numPins);

    // Destructor

    // Override the writeToDisplay method
    void updateValue(const SensorData& data);

    // Additional methods for Servo
};

#endif // SERVO_H
