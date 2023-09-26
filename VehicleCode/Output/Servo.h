#ifndef SERVO_H
#define SERVO_H

#include "Actuator.h"  // Include the header for the Actuator class

class Servo : public Actuator {
private:
    // Additional attributes specific to Servo, if any

public:
    // Constructor
    Servo(int* pins, int numPins);

    // Destructor (if needed)

    // Override the writeToDisplay method
    void writeToDisplay() override;

    // Additional methods for Servo, if any
};

#endif // SERVO_H
