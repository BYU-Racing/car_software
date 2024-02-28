#include "ThrottleSensor.h"
#include <Arduino.h>

#define MAXPERCENT 10000
#define LENGTH 8
#define BYTESIZE 256
#define ERROR_TOL 1000
#define MAINTAIN_TOL 2
#define SHUTDOWN_TOL 500
#define ID_ERROR 0
#define ERROR_LENGTH 6
#define SHUTDOWN 1
#define NO_SHUTDOWN 0
#define WARNING 1
#define CRITICAL 2
#define FATAL 3

//**Global Variables
int torque;

/**
 * @brief Constructor for ThrottleSensor class.
 *
 * Initializes an ThrottleSensor object with specified parameters.
 *
 * @param id (int) The unique identifier for the sensor.
 * @param freq (int) The update delay of the sensor in milliseconds.
 * @param inPins (int) The input pin id for the analog sensor.
 */
ThrottleSensor::ThrottleSensor(int id, int waitTime, int inPin1, int inPin2, int bias, int max, int dataLength) {
    sensorID = id;
    this->waitTime = waitTime;
    previousUpdateTime = millis();
    inputPins[0] = inPin1;
    inputPins[1] = inPin2;
    throttle1 = 0;
    throttle2 = 0;
    torque = 200;
    this->bias = bias;
    this->max = max;
    this->dataLength = dataLength;
    sendData = new int[LENGTH];
};

/**
 * @brief Read analog sensor inputs.
 * Updates the sensor value by reading the analog input pin.
 * @return (int) The current sensor value.
 */
int ThrottleSensor::readInputs() {

    //Update previous update time
    previousUpdateTime = millis();

    //Grab Sensor Value
    throttle1 = map(analogRead(inputPins[0]), bias, max, 0, MAXPERCENT);
    throttle2 = map(-analogRead(inputPins[1]), -max, -bias, 0, MAXPERCENT);

    //Return a pointer to the private value
    if (checkError(throttle1, throttle2)) {
      return (throttle1 + throttle2) / 2;
    }
    if (countMismatch > SHUTDOWN_TOL) {
        command = SHUTDOWN;
        errorType = FATAL;
        return -1;
    }
    return 0;
}


/**
 * @brief Check if both throttle sensors are within ERROR_TOL of each other.

 * @param percent1 (int) The percent value recorded by throttle 1.
 * @param percent2 (int) The percent value recorded by throttle 2.
 * 
 * @return (bool) True if the number of consequetive mismatches is less than MAINTAIN_TOL,
 *                  False otherwise.
*/
bool ThrottleSensor::checkError(int percent1, int percent2) {
    
    // update countMismatch
    if (abs(percent1 - percent2) < ERROR_TOL) {
      countMismatch = 0;
    }
    else {
      countMismatch++;
    }

    // return the status of the error
    return countMismatch <= MAINTAIN_TOL;
}


/**
 * @brief Builds the data array for the CAN message.
 * 
 * @param torque (int) The torque value to be sent.
 * @param percent (int) The percent value to be sent.
 * 
 * @return (int*) The data array for the CAN message.
*/
int* ThrottleSensor::buildData(int percent){
    // determine torque
    torque = computeTorque(percent);

    // convert to motor controller format

    // construct formatted data
    sendData[0] = getLow(torque); //torqueLow
    sendData[1] = getHigh(torque); //torqueHigh
    sendData[2] = getLow(percent); //speedLow
    sendData[3] = getHigh(percent); //speedHigh
    sendData[4] = 1;
    sendData[5] = 1;
    sendData[6] = 0;
    sendData[7] = 0;

    return sendData;
}

/**
 * @brief Sends an error message.
 * 
 * @param sendData (int*) The data array for the CAN message.
 * @param command (int) The command to be sent.
 *                          0: No shutdown
 *                          1: Shutdown
 * @param errorType (int) The type of error.
 *                          0: No Error
 *                          1: Warning
 *                          2: Critical
 *                          3: Fatal
*/
int* ThrottleSensor::buildError() {
    sendData[0] = sensorID;
    sendData[1] = command;
    sendData[2] = errorType;
    sendData[3] = countMismatch;
    sendData[4] = throttle1;
    sendData[5] = throttle2;
    return sendData;
}

/**
 * @brief Compute the torque value from the percent value.
 * @param percent (int) The percent value to be converted.
 * @return (int) The torque value.
*/
int ThrottleSensor::computeTorque(int percent) {
  return torque; // 200
}


/**
 * @brief Transform the sensor data into new scale.
 * @param data (int) The data to be rescaled.
 * @return (int) The rescaled data.
 */
int ThrottleSensor::rescale(int data) {
    //Transform data
    return map(data, bias, max, 0, MAXPERCENT);
};

/**
 * @brief Gets the low byte of a percent value.
 * @param percent (int) The percent value to be converted.
 * @return (int) The low byte of the percent value.
*/
int ThrottleSensor::getLow(int percent) {
  return percent % BYTESIZE;
}


/**
 * @brief Gets the high byte of a percent value.
 * @param percent (int) The percent value to be converted.
 * @return (int) The high byte of the percent value.
*/
int ThrottleSensor::getHigh(int percent) {
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
bool ThrottleSensor::readyToCheck() {
    //millis gets arduino time
    return (waitTime <= int(millis() - previousUpdateTime));
};

/**
 * @brief Get the unique identifier for the sensor.
 * @return (int) The sensor identifier.
 */
int ThrottleSensor::getId() {
    return sensorID;
}

/**
 * @brief Get the input pin of the analog sensor.
 * @return (int) The input pin number.
 */
int ThrottleSensor::getPins() {
    return inputPins[0];
}

/**
 * @brief Get the update frequency wait time.
 * @return (int) The update frequency wait time in milliseconds.
 */
int ThrottleSensor::getWaitTime() {
    return waitTime;
}

/**
 * @brief Get the length of the data array.
 * @return (int) The length of the data array.
 */
int ThrottleSensor::getDataLength() {
    return dataLength;
}

/**
 * @brief Set the input pin for the analog sensor.
 * @param inPins (int) The new input pin number.
 */
void ThrottleSensor::setPin(int inPin, int index=0) {
    inputPins[index] = inPin;
}

/**
 * @brief Set the update frequency wait time.
 * @param inWait (int) The new update frequency wait time in milliseconds.
 */
void ThrottleSensor::setWaitTime(int inWait) {
    waitTime = inWait;
}

/**
 * @brief Set the unique identifier for the sensor.
 * @param inId (int) The new sensor identifier.
 */
void ThrottleSensor::setId(int inId) {
    sensorID = inId;
}