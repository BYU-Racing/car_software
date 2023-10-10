#include "Dashboard.h"
#include "Actuator.h"
#include "Screen.h"
#include "LEDArray.h"
#include "Servo.h"
#include "Horn.h"
#include "../SensorID.h"

// #include <Arduino.h>
// #include <FlexCAN_T4.h>

// Global variables
#define BAUDRATE 250000


// CHECK: define function
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
    this->display = display;
    numActuators = sizeof(display);

    // Initialize CAN bus
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
    can2.begin();
    can2.setBaudRate(BAUDRATE);
}

// TEST: define function
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


// CHECK: define function
/*!
 * @brief Get the index of a sensor in the display array
 * 
 * @param sensor (SensorID) The sensor ID
 * @return (int) The index of the sensor in the display array
 */
int getSensorIndex(int id) {
    switch (id) {
        case SEVEN_SEG_1: return 0;     //SEVEN_SEG_1
        case SEVEN_SEG_2: return 1;     //SEVEN_SEG_2
        case LED_ARRAY_1: return 2;     //LED_ARRAY_1
        case LED_ARRAY_2: return 3;     //LED_ARRAY_2
        case LED_ARRAY_3: return 4;     //LED_ARRAY_3
        case SERVO:       return 5;     //SERVO
        case HORN:        return 6;     //HORN
        default: return -1;             //UNKNOWN
    }
}


// TEST: define function
/*!
 * @brief Update the driver's display
 * Reads data from the CAN bus and updates the display based on the data.
 * 
 * @param None
 * @return None
 */
void Dashboard::updateDisplay() {
    CAN_message_t rmsg;
    if (can2.read(rmsg)) {
        // Determine which actuator to update based on the received CAN message and update it
        int actuatorIndex = getSensorIndex(rmsg.buf[0]); 
        if (actuatorIndex >= 0 && actuatorIndex < numActuators) {
            SensorData* sensorData = new SensorData(rmsg);
            display[actuatorIndex]->updateValue(sensorData);
            delete sensorData;
        }
    }
}
