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

// EDIT: define function
/*!
 * @brief Constructor
 * Initializes the CAN bus and the actuators
 * 
 * @param startTime (unsigned long) The time the car started
 * @return None
*/
Dashboard::Dashboard(unsigned long startTime) {
    // load parameters
    this->startTime = startTime;

    // Initialize CAN bus
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
    can2.begin();
    can2.setBaudRate(BAUDRATE);

    // Instantiate the actuators
    // TODO include pin information
    Screen* lapScreen = new Screen();
    Screen* totalScreen = new Screen(); 
    LEDArray* batteryLife = new LEDArray(); 
    LEDArray* batteryDraw = new LEDArray(); 
    LEDArray* batteryTemp = new LEDArray(); 
    Servo* speed = new Servo(); 
    Horn* horn = new Horn(); 
    
    // Declare and initialize the display array of pointers
    Actuator* display[] = {
                            (Actuator*)lapScreen, (Actuator*)totalScreen, 
                            (Actuator*)batteryLife, (Actuator*)batteryDraw, (Actuator*)batteryTemp, 
                            (Actuator*)speed, 
                            (Actuator*)horn
                        };

    numActuators = sizeof(display);
}

// CHECK: define function
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

// EDIT: define function. idk if this is the most efficient approach
/*!
 * @brief Get the index of a sensor in the display array
 * 
 * @param sensor (SensorID) The sensor ID
 * @return (int) The index of the sensor in the display array
 */
int getSensorIndex(int id) {
    SensorID sensorID = getSensorID(id);
    switch (sensorID) {
        case SEVEN_SEG_1: return 0;
        case SEVEN_SEG_2: return 1;
        case LED_ARRAY_1: return 2;
        case LED_ARRAY_2: return 3;
        case LED_ARRAY_3: return 4;
        case SERVO:       return 5;
        case HORN:        return 6;
        default: return -1;
    }
}


// TODO: define function
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
