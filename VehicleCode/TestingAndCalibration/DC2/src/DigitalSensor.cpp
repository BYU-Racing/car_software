#include "DigitalSensor.h"


/*!
 * @brief Constructor
 * Initializes the sensor
 * 
 * @param id (int) The ID of the sensor
 * @param freq (int) The frequency at which the sensor should be read
 * @param pin (int) An array of ints representing the input pins
 * @return None
 */
DigitalSensor::DigitalSensor(int id, int time, int pin, bool isCritical) {
    sensorID = id;
    waitTime = time;
    inputPins[0] = pin;
    pinMode(inputPins[0], INPUT_PULLDOWN);
    sensorValue = 0;
    previousUpdateTime = millis();
    critical = isCritical;
};


/*! 
 * @brief Read inputs
 * Reads the digital sensor value and returns it
 * 
 * @param None
 * @return sensorValue (int*) A pointer to an array of ints representing the sensor value
 */
int DigitalSensor::readInputs() {
    //Update previous update time
    previousUpdateTime = millis();

    //Grab Sensor Value
    sensorValue = digitalRead(inputPins[0]);

    //Return a pointer to the private value
    return sensorValue;
};


/*! 
 * @brief Get ID
 * Returns the ID of the sensor
 * 
 * @param None
 * @return sensorID (int) The ID of the sensor
 */
int DigitalSensor::getId(){
    return sensorID;
};


/*! 
 * @brief Get input pin
 * Returns the pin that the sensor is connected to
 * 
 * @param None
 * @return input pin (int) The pin of the sensor
 */
int DigitalSensor::getPins(){
    return inputPins[0];
};


/*! 
 * @brief Get wait time
 * Returns the time that the sensor waits between
 * reporting. In milliseconds
 * 
 * @param None
 * @return waitTime (int) The wait time of the sensor
 */
int DigitalSensor::getWaitTime(){
    return waitTime;
};


/*! 
 * @brief Get data length
 * Returns the length of the data array. For 
 * digital sensors this will always be 1
 * 
 * @param None
 * @return 1 (int) The length of the data
 */
int DigitalSensor::getDataLength(){
    return 1;
};


/*!
 * @brief Builds the data array for the CAN message.
 * 
 * @param torque (int) The torque value to be sent.
 * @param percent (int) The percent value to be sent.
 * 
 * @return (int*) The data array for the CAN message.
*/
int* DigitalSensor::buildData(int value) {
    return new int[1]{value};
};

/*!
 * @brief Builds the error data array for the CAN message.
 * 
 * @param errorType (int) The type of error.
 * @param errorData (int*) The data associated with the error.
 * 
 * @return (int*) The error data array for the CAN message.
*/
int* DigitalSensor::buildError() {
    return new int[1]{0};
}

/*!
 * @brief Transform the sensor data into new scale.
 * @param data (int) The data to be rescaled.
 * 
 * Digital Sensors will not need to be rescaled
 * 
 * @return -1 because this should not be used
 */
int DigitalSensor::rescale(int data) {
    //Transform data
    return -1;
};

bool DigitalSensor::readyToCheck() {
    return (waitTime <= int(millis() - previousUpdateTime));
}


bool DigitalSensor::getCritical() {
    return critical;
}

bool DigitalSensor::plugTest() {
    // Change pinMode twice
    pinMode(inputPins[0], INPUT_PULLDOWN);
    if (digitalRead(inputPins[0]) == 0) {
        pinMode(inputPins[0], INPUT_PULLUP);
        if(digitalRead(inputPins[0] == 0)) {
            pinMode(inputPins[0], INPUT_PULLDOWN);
            return true;
        }
    }
    pinMode(inputPins[0], INPUT_PULLDOWN);
    return false;
}