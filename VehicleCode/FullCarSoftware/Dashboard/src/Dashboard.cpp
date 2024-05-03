#include "Dashboard.h"
#include "Actuator.h"
#include "LEDArray.h"
#include "Servo.h"
#include "SensorID.h"


// Global variables
#define BAUDRATE 250000


/*!
 * @brief Constructor
 * Initializes the CAN bus and the actuators
 * 
 * @param display (Actuator**) An array of pointers to Actuator objects
 * @param startTime (unsigned long) The time the car started
 * @return None
*/
Dashboard::Dashboard(Actuator** display, unsigned long startTime) {
    // load parameters
    this->startTime = startTime;

    Serial.println("AFTER STIME");
    this->display = display;
    Serial.println("AFTER DISPLAY");
    numActuators = sizeof(display);

    Serial.println("AFTER PARAMETER LOAD");
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
    for (int i = 0; i < numActuators; i++) {
        delete display[i];
    }
}


/*!
 * @brief Get the index of a sensor in the display array
 * 
 * @param sensor (SensorID) The sensor ID
 * @return (int) The index of the sensor in the display array
 */
int Dashboard::getSensorIndex(int id) {
    switch (id) {
        case 1000: return 0;     //SEVEN_SEG_1
        case 0x37: return 0;     //LED_ARRAY_1
        case LED_ARRAY_2: return 2;     //LED_ARRAY_2
        case LED_ARRAY_3: return 3;     //LED_ARRAY_3
        case SERVO:       return 4;     //SERVO
        case HORN:        return 5;     //HORN
        default: return -1;             //UNKNOWN
    }
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
        // Determine which actuator to update based on the received CAN message and update it
        Serial.print("ID: ");
        Serial.println(rmsg.id);
        int actuatorIndex = getSensorIndex(rmsg.id); 

        if (actuatorIndex >= 0 && actuatorIndex < numActuators) { // This will break cause num actuators is min 1 and the return can be 0
            SensorData* sensorData = new SensorData(rmsg);
            sensorData->toString();
            display[actuatorIndex]->updateValue(*sensorData);
            delete sensorData;
        }
        delay(10);
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