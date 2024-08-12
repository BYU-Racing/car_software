 #include "Dashboard.h"
#include "Actuator.h"
#include "LEDArray.h"
#include "Servo.h"
#include "SensorID.h"


// Global variables
#define BAUDRATE 250000

#define SWITCH_ID 1
#define BATTERY_TEMP_ID 54
#define TRACTIVE_ID 194
#define BRAKE_ID 4
/*!
 * @brief Constructor
 * Initializes the CAN bus and the actuators
 * 
 * @param display (Actuator**) An array of pointers to Actuator objects
 * @param startTime (unsigned long) The time the car started
 * @return None
*/
Dashboard::Dashboard(EasyNex inDisplay) {
    // load display
    display = inDisplay;

}


/*!
 * @brief Destructor
 * Deletes the actuators
 * 
 * @param None
 * @return None
*/
Dashboard::~Dashboard() {
    // Delete the actuators
    int x = 12;
}

/*!
 * @brief Update the driver's display
 * Reads data from the CAN bus and updates the display based on the data.
 * 
 * @param None
 * @return None
 */
void Dashboard::updateDisplay() {
    CAN_message_t rmsg;
    if (this->can1.read(rmsg)) {
        SensorData* msg = new SensorData(rmsg);
        routeData(msg);
    }
}

void Dashboard::routeData(SensorData* data) {
    // Routes the message to the correct dash control function
    switch (data->getId()) {
        case SWITCH_ID:
            updateSwitchState(data);
            break;
        case TRACTIVE_ID:
            updateTractiveState(data);
            break;
        case BRAKE_ID:
            updateBrakeState(data);
            break;
        case BATTERY_TEMP_ID:
            updateBatteryTemp(data);
            break;
        case BATTERY_PERC_ID:
            updateBatteryPerc(data);
            break;
    }

}

/**
 * @brief Set the CAN bus
 * 
 * @param canIN (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
void Dashboard::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIN) {
    this->can1 = canIN;
}


/**
 * @brief Reset the time zero
 * @param startTime (unsigned long) The time the car started
 */
void Dashboard::resetTimeZero(unsigned long startTime) {
    this->startTime = startTime;
}


//CONTROL FUNCTIONS//
void Dashboard::updateSwitchState(SensorData* data) {
    // Get the current state && update all SWITCH COMPONENTS!!!
    if(data->getData() == 0) {
        display.writeNum("SwitchVar", 0);
    }
    else {
        display.writeNum("SwitchVar", 1);
    }
}

void Dashboard::updateSOCState(SensorData* data) {
    //TODO: Check the units this comes from the BMS in
    display.writeNum("SOC", data->getData());
}

void Dashboard::updateTractiveActiveState(SensorData* data){ 
    if(data->getData() == 0) {
        display.writeNum("TractiveActive", 0);
    }
    else {
        display.writeNum("TractiveActive", 1);
    }
}

void Dashboard::updateBrakeActiveState(SensorData* data) {
    if(data->getData() == 0) {
        display.writeNum("BrakeActive", 0);
    }
    else {
        display.writeNum("BrakeActive", 1);
    }
}

void Dashboard::updateStartFaultState(SensorData* data) {
    if(data->getData() == 0) {
        display.writeNum("StartFault", 0);
    }
    else {
        display.writeNum("StartFault", 1);
    }
}