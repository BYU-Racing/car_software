#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Actuator.h"  // Include the header for the Actuator class

class Dashboard {
private:
    Actuator** display;   // Array of pointers to Actuator objects
    int numActuators;     // Number of actuators
    int timeZero;         // Starting time

public:
    // Constructor
    Dashboard(int numActuators, int startTime);

    // Destructor
    ~Dashboard();

    // Method to read data from the CAN bus
    void readCANBus();

    // Method to update the display based on sensor data
    void updateDisplay();
};

#endif // DASHBOARD_H
