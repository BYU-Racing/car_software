 #include "Dashboard.h"


// Global variables
#define BAUDRATE 250000

#define SWITCH_ID 1
#define BATTERY_TEMP_ID 54
#define TRACTIVE_ID 194
#define BRAKE_ID 4
#define DRIVE_STATE_ID 203
#define BRAKE_P 4
#define THROTTLE1_ID 2
#define THROTTLE2_ID 3

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
    currDriveState = 0;
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

    display.NextionListen();
}

void Dashboard::routeData(SensorData* data) {
    // Routes the message to the correct dash control function
    switch (data->getId()) {
        case SWITCH_ID:
            updateSwitchState(data);
            break;
        case TRACTIVE_ID:
            updateTractiveActoveState(data);
            break;
        case BRAKE_ID:
            updateBrakeActiveState(data);
            break;
        case BATTERY_TEMP_ID:
            //updateBatteryTemp(data);
            break;
        case BATTERY_PERC_ID:
            updateSOCState(data);
            break;
        case THROTTLE1_ID:
            updateThrottle1(data);
            break;
        case THROTTLE2_ID:
            updateThrottle2(data);
            break;
        case DRIVE_STATE_ID:
            updateDriveState(data);
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
    if(data->getData()[0] != switchState) {
        if(data->getData()[0] == 0) {
            display.writeNum("PreRun.SwitchVar.val", 0);
        }
        else {
            display.writeNum("PreRun.SwitchVar.val", 1);
        }
        switchState = data->getData()[0];
    }
}

void Dashboard::updateSOCState(SensorData* data) {
    //TODO: Check the units this comes from the BMS in

    if(data->getData()[0] != SOCState) {
        display.writeNum("PreRun.SOC.val", data->getData());
        SOCState = data->getData()[0];
    }

}

void Dashboard::updateTractiveActiveState(SensorData* data){ 

    if(data->getData()[0] != TractiveState) {
        if(data->getData()[0] == 0) {
            display.writeNum("PreRun.TractiveActive.val", 0);
        }
        else {
            display.writeNum("PreRun.TractiveActive.val", 1);
        }
        TractiveState = data->getData()[0];
    }

}

void Dashboard::updateBrakeActiveState(SensorData* data) {
    //Update Pressure
    if(((data->getData()[0] * 100) + data->getData()[1]) != BrakePState) {
        display.writeNum("PreRun.BrakeP.val", ((data-getData()[0] * 100) + data->getData()[1]))
    }


    BrakeActiveHandoff = (((data->getData()[0] * 100) + data->getData()[1]) > 50);
    //Update Active
    if(BrakeActiveHandoff != BrakeActiveState) {
        if(BrakeActiveHandoff == 0) {
            display.writeNum("PreRun.BrakeActive.val", 0);
        }
        else {
            display.writeNum("PreRun.BrakeActive.val", 1);
        }
        BrakeActiveState=BrakeActiveHandoff;
    }
}

void Dashboard::updateStartFaultState(SensorData* data) {

    if(StartFaultState != data->getData()[0]) {
        if(data->getData()[0] == 0) {
            display.writeNum("PreRun.StartFault.val", 0);
        }
        else {
            display.writeNum("PreRun.StartFault.val", 1);
        }
    }

}

void Dashboard::updateDriveState(SensorData* data) {
    if(data->getData()[0] == 0 && currDriveState == 1) {
        display.writeStr("page Running");
        currDriveState = 0;
    }

    if(data->getData()[0] == 1 && currDriveState == 0) {
        display.writeStr("page PreRun");
        currDriveState = 1;
    }
}

void Dashboard::updateThrottle1(SensorData* data) {
    tempThrottle = (data->getData()[0] * 100) + data->getData()[1];

    if(tempThrottle != throttle1State) {
        display.writeNum("PreRun.Throttle1Val.val", tempThrottle);
        throttle1State = tempThrottle;
    }
    
}

void Dashboard::updateThrottle2(SensorData* data) {
    tempThrottle = (data->getData()[0] * 100) + data->getData()[1];

    if(tempThrottle != throttle2State) {
        display.writeNum("PreRun.Throttle2Val.val", tempThrottle);
        throttle2State = tempThrottle;
    }
    
}