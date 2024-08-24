#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "EasyNextionLibrary.h"
#include "SensorData.h"

class Dashboard {
private:
    // Instantiate attributes
    unsigned long startTime;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
    EasyNex* display;
    
    int currDriveState;
    int tempThrottle;


    int switchState = 0;
    int SOCState = 0;
    int TractiveState = 0;
    int BrakeActiveState = 0;
    int BrakePState = 0;
    int BrakeActiveHandoff = 0;
    int StartFaultState = 0;
    int throttle1State = 0;
    int throttle2State = 0;

public:
    // Constructor
    Dashboard();
    void setDisplay(EasyNex* inDisplay);

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
    void updateDriveState(SensorData* data);
    void updateThrottle1(SensorData* data);
    void updateThrottle2(SensorData* data);
};

#endif // DASHBOARD_H