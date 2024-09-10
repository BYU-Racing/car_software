#include "AnalogSensor.h"
#include <Arduino.h>

constexpr int ACCELERATOR_POT_1 = 3;
constexpr int MAXPERCENT = 10000;
constexpr int LENGTH = 8;
constexpr int BYTESIZE = 256;

/**
 * @brief Constructor for AnalogSensor class.
 *
 * Initializes an AnalogSensor object with specified parameters.
 *
 * @param id (int) The unique identifier for the sensor.
 * @param waitTime (int) The update delay of the sensor in milliseconds.
 * @param inPins (int) The input pin id for the analog sensor.
 */
AnalogSensor::AnalogSensor(int id, int waitTime, int inPin, bool inCritical) {
    sensorID = id;
    this->waitTime = waitTime;
    previousUpdateTime = millis();
    inputPins[0] = inPin;
    sensorValue = 0;
    this->dataLength = 2;
    isCritical = inCritical;
};

/**
 * @brief Read analog sensor inputs.
 * Updates the sensor value by reading the analog input pin.
 * @return (int) The current sensor value.
 */
int AnalogSensor::readInputs() {

    //Update previous update time
    previousUpdateTime = millis();

    //Grab Sensor Value
    sensorValue = analogRead(inputPins[0]);

    //Returns sensorValue but limits it to 1023
    return (sensorValue < 1023) ? sensorValue : 1023;
    
};


/**
 * @brief Builds the data array for the CAN message. Expected input is the analog sensor raw value that is read
 * Expected output is a 2 item array that contains [1000s place 100s place, 10s place 1s place]
 * EX: 1023 -> [10, 23] and 921 -> [9, 21] 
 * 
 * @param int value value that was read from the sensor allows for it to be converted to CAN format
 * 
 * @return (int*) The data array for the CAN message.
*/
int* AnalogSensor::buildData(int value) {

    return new int[2]{(value / 100), (value - ((value / 100) * 100))};
}

/**
 * @brief Builds the error data array for the CAN message.
 * 
 * @param errorType (int) The type of error.
 * @param errorData (int*) The data associated with the error.
 * 
 * @return (int*) The error data array for the CAN message.
*/
// TODO: implement this method
int* AnalogSensor::buildError() {
    return new int[1]{0};
}

/**
 * @brief Transform the sensor data into new scale.
 * @param data (int) The data to be rescaled.
 * @return (int) The rescaled data.
 */
int AnalogSensor::rescale(int data) {
    //Transform data
    return data;
};



/**
 * @brief Check if the sensor is ready for the next update.
 *
 * Determines if the elapsed time since the last update is greater than or equal to 
 * the specified wait time.
 *
 * @return (bool) True if the sensor is ready for the next update, false otherwise.
 */
bool AnalogSensor::readyToCheck() {
    //millis gets arduino time
    return (waitTime <= int(millis() - previousUpdateTime));
};

/**
 * @brief Get the unique identifier for the sensor.
 * @return (int) The sensor identifier.
 */
int AnalogSensor::getId() {
    return sensorID;
}

/**
 * @brief Get the input pin of the analog sensor.
 * @return (int) The input pin number.
 */
int AnalogSensor::getPins() {
    return inputPins[0];
}

/**
 * @brief Get the update frequency wait time.
 * @return (int) The update frequency wait time in milliseconds.
 */
int AnalogSensor::getWaitTime() {
    return waitTime;
}

/**
 * @brief Get the length of the data array.
 * @return (int) The length of the data array.
 */
int AnalogSensor::getDataLength() {
    return dataLength;
}

/**
 * @brief Set the input pin for the analog sensor.
 * @param inPin (int) The new input pin number.
 */
void AnalogSensor::setPin(int inPin, int index=0) {
    inputPins[index] = inPin;
}

/**
 * @brief Set the update frequency wait time.
 * @param inWait (int) The new update frequency wait time in milliseconds.
 */
void AnalogSensor::setWaitTime(int inWait) {
    waitTime = inWait;
}

/**
 * @brief Set the unique identifier for the sensor.
 * @param inId (int) The new sensor identifier.
 */
void AnalogSensor::setId(int inId) {
    sensorID = inId;
}

bool AnalogSensor::getCritical() {
    return isCritical;
}

bool AnalogSensor::plugTest() {
    if(analogRead(inputPins[0]) == 0) {
        return true;
    }
    return false;
}