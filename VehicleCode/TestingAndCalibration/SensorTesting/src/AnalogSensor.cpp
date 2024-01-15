#include "AnalogSensor.h"
#include <Arduino.h>

/**
 * @brief Constructor for AnalogSensor class.
 *
 * Initializes an AnalogSensor object with specified parameters.
 *
 * @param id (int) The unique identifier for the sensor.
 * @param freq (int) The update delay of the sensor in milliseconds.
 * @param inPins (int) The input pin id for the analog sensor.
 */
AnalogSensor::AnalogSensor(int id, int freq, int inPins) {
    sensorID = id;
    waitTime = freq;
    previousUpdateTime = millis();
    inputPins[0] = inPins;
    inputPins[4] = -1;
    sensorValue = 0;
};

/**
 * @brief Read analog sensor inputs.
 *
 * Updates the sensor value by reading the analog input pin.
 *
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
 * @brief Get the input pin of the analog sensor.
 *
 * @return (int) The input pin number.
 */
int AnalogSensor::getPins() {
    return inputPins[0];
}

/**
 * @brief Get the update frequency wait time.
 *
 * @return (int) The update frequency wait time in milliseconds.
 */
int AnalogSensor::getWaitTime() {
    return waitTime;
}

/**
 * @brief Set the input pin for the analog sensor.
 *
 * @param inPins (int) The new input pin number.
 */
void AnalogSensor::setPin(int inPins) {
    inputPins[0] = inPins;
}

/**
 * @brief Set the update frequency wait time.
 *
 * @param inWait (int) The new update frequency wait time in milliseconds.
 */
void AnalogSensor::setWaitTime(int inWait) {
    waitTime = inWait;
}

/**
 * @brief Set the unique identifier for the sensor.
 *
 * @param inId (int) The new sensor identifier.
 */
void AnalogSensor::setId(int inId) {

    sensorID = inId;
}