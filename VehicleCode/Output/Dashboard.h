#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Actuator.h"

class Dashboard {
private:
    // Instantiate attributes
    Actuator** display;
    int numActuators;
    int timeZero;

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
