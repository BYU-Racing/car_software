#include "Dashboard.h"
#include "Actuator.h"
#include "LEDArray.h"
#include "Servo.h"
#include "SensorID.h"

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

    Serial.println("AFTER STIME");
    this->display = display;
    Serial.println("AFTER DISPLAY");
    numActuators = sizeof(display);

    Serial.println("AFTER PARAMETER LOAD");

    // Initialize CAN bus
    // FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can2;
    // can2.begin();
    // can2.setBaudRate(BAUDRATE);

    Serial.println("AFTER CAN START");
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
int Dashboard::getSensorIndex(int id) {
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

    //Serial.println("Ran Function");
    CAN_message_t rmsg;
    if (this->can1.read(rmsg)) {
        Serial.println("GOT CAN");
        // Determine which actuator to update based on the received CAN message and update it
        Serial.print("ID: ");
        Serial.println(rmsg.id);
        int actuatorIndex = getSensorIndex(rmsg.id); 

        Serial.print("ACTUATOR INDEX: ");
        Serial.println(actuatorIndex);

        //Serial.print("BAT%: ");
        //Serial.println(rmsg.buf[0]);
        if (actuatorIndex >= 0 && actuatorIndex < numActuators) { // This will break cause num actuators is min 1 and the return can be 0
            SensorData* sensorData = new SensorData(rmsg);
            display[actuatorIndex]->updateValue(*sensorData);
            delete sensorData;
        }
        delay(500);
    }
}

void Dashboard::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIN) {
    this->can1 = canIN;
}
