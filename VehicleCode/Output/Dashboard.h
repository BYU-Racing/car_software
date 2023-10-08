// CHECK add docstring
/*!
 * @brief Read CAN bus data and update the display
 * Whenever updateDisplay gets called, this class reads data from the CAN bus
 * and updates the appropriate display object based on the data.
 * 
 * @param startTime (unsigned long) The time that the program started in milliseconds
 * @return None
*/

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Actuator.h"

class Dashboard {
private:
    // Instantiate attributes
    Actuator** display;
    int numActuators;
    // CHECK change startTime to unsigned long
    unsigned long startTime;

    // CHECK add getSensorIndex method
    int getSensorIndex(SensorID sensor);

public:
    // Constructor
    // CHECK change startTime to unsigned long
    // CHECK remove numActuators, Dashboard should decide how many actuators there are
    Dashboard(unsigned long startTime);

    // Destructor
    ~Dashboard();

    // Method to update the display based on sensor data
    void updateDisplay();

    // CHECK remove readCANBus 
    // Method to read data from the CAN bus
    // void readCANBus();
};

#endif // DASHBOARD_H
