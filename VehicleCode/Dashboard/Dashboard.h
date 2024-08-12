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
#include "EasyNextionLibrary.h"

class Dashboard {
private:
    // Instantiate attributes
    unsigned long startTime;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
    EasyNex display;


    int getSensorIndex(int id);

public:
    // Constructor
    Dashboard(EasyNex inDisplay);

    // Destructor
    ~Dashboard();

    // Method to update the display based on sensor data
    void updateDisplay();
    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIN);
    void resetTimeZero(unsigned long startTime);
    void routeData(SensorData* data);

    //Control functions
    void updateSwitchState(SensorData* data);
    void updateSOCState(SensorData* data);
    void updateTractiveActiveState(SensorData* data);
    void updateBrakeActiveState(SensorData* data);
    void updateStartFaultState(SensorData* data);
};

#endif // DASHBOARD_H