#include "AnalogSensor.h"
#include <Arduino.h>

#define ACCELERATOR_POT_1 3
#define ACCELERATOR_POT_2 4
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
AnalogSensor::AnalogSensor(int id, int waitTime, int inPins, int bias, int max, int dataLength) {
    sensorID = id;
    this->waitTime = waitTime;
    previousUpdateTime = millis();
    inputPins[0] = inPins;
    inputPins[4] = -1;
    sensorValue = 0;
    this->bias = bias;
    this->max = max;
    this->dataLength = dataLength;
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
    sensorValue = rescale(analogRead(inputPins[0]));

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
int* AnalogSensor::buildData(int torque, int percent){
    // convert to motor controller format
    int torqueLow = getLow(torque);
    int torqueHigh = getHigh(torque);
    int speedLow = getLow(percent);
    int speedHigh = getHigh(percent);

    // construct formatted data
    int* sendData = new int[LENGTH];
    sendData[0] = torqueLow;
    sendData[1] = torqueHigh;
    sendData[2] = speedLow;
    sendData[3] = speedHigh;
    sendData[4] = 1;
    sendData[5] = 1;
    sendData[6] = 0;
    sendData[7] = 0;

    return sendData;
}
int* AnalogSensor::buildData(int value) {
    return new int[1]{value};
}

/**
 * @brief Transform the sensor data into new scale.
 * @param data (int) The data to be rescaled.
 * @return (int) The rescaled data.
 */
int AnalogSensor::rescale(int data) {
    //Transform data
    if (sensorID == ACCELERATOR_POT_1 || sensorID == ACCELERATOR_POT_2) {
        return map(data, bias, max, 0, MAXPERCENT);
    } 
    return data;
};

/**
 * @brief Gets the low byte of a percent value.
 * @param percent (int) The percent value to be converted.
 * @return (int) The low byte of the percent value.
*/
int getLow(int percent) {
  return percent % BYTESIZE;
}


/**
 * @brief Gets the high byte of a percent value.
 * @param percent (int) The percent value to be converted.
 * @return (int) The high byte of the percent value.
*/
int getHigh(int percent) {
  return percent / BYTESIZE;
}



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
 * @param inPins (int) The new input pin number.
 */
void AnalogSensor::setPin(int inPins) {
    inputPins[0] = inPins;
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