#include "AnalogSensor.h"
#include <Arduino.h>

#define ACCELERATOR_POT_1 3
#define MAXPERCENT 10000
#define LENGTH 8
#define BYTESIZE 256

/**
 * @brief Constructor for AnalogSensor class.
 *
 * Initializes an AnalogSensor object with specified parameters.
 *
 * @param id (int) The unique identifier for the sensor.
 * @param freq (int) The update delay of the sensor in milliseconds.
 * @param inPins (int) The input pin id for the analog sensor.
 */
AnalogSensor::AnalogSensor(int id, int waitTime, int inPin) {
    sensorID = id;
    this->waitTime = waitTime;
    previousUpdateTime = millis();
    inputPins[0] = inPin;
    sensorValue = 0;
    // this->bias = bias;
    // this->max = max;
    this->dataLength = 2;
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

    //Return a pointer to the private value
    return sensorValue;
    
};


/**
 * @brief Builds the data array for the CAN message.
 * 
 * @param torque (int) The torque value to be sent.
 * @param percent (int) The percent value to be sent.
 * 
 * @return (int*) The data array for the CAN message.
*/
int* AnalogSensor::buildData(int value) {

    int first = value / 100;
    int second;

    second = value - (first * 100);




    return new int[2]{first, second};
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
    return map(data, bias, max, 0, MAXPERCENT);
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