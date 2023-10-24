// CHECK all
#include "DigitalSensor.h"
#include "../SensorID.h"


// CHECK Constructor
/*!
 * @brief Constructor
 * Initializes the sensor
 * 
 * @param id (int) The ID of the sensor
 * @param freq (int) The frequency at which the sensor should be read
 * @param prio (int) The priority of the sensor
 * @param inputPins (int*) An array of ints representing the input pins
 * @return None
 */
DigitalSensor::DigitalSensor(int id, int freq, int prio, int* inputPins) {
    this->sensorID = id;
    this->waitTime = freq;
    this->priority = prio;
    this->inputPins = inputPins;
    this->sensorValue = {0};
    this->previousUpdateTime = millis();
};


// CHECK Destructor
/*! 
 * @brief Destructor
 * Deletes the sensorValue and inputPins arrays
 *
 * @param None
 * @return None
 */
DigitalSensor::~DigitalSensor() {
    // delete sensorValue
    delete[] sensorValue;
    delete[] inputPins;
};


// CHECK readInputs
/*! 
 * @brief Read inputs
 * Reads the digital sensor value and returns it
 * 
 * @param None
 * @return sensorValue (int*) A pointer to an array of ints representing the sensor value
 */
int* DigitalSensor::readInputs() {
    //Update previous update time
    previousUpdateTime = millis();

    //Grab Sensor Value
    sensorValue[0] = digitalRead(inputPins[0]);

    //Return a pointer to the private value
    return sensorValue;
};


// CHECK readyToCheck
/*! 
 * @brief Ready to check
 * Determines whether the sensor is ready to be read
 * 
 * @param None
 * @return (bool) True if the sensor is ready to be read, false otherwise
 */
bool DigitalSensor::readyToCheck() {
    //millis gets arduino time
    return (waitTime <= millis() - previousUpdateTime);
};


// CHECK getId
/*! 
 * @brief Get ID
 * Returns the ID of the sensor
 * 
 * @param None
 * @return sensorID (int) The ID of the sensor
 */
int DigitalSensor::getId() const {
    return sensorID;
};


// CHECK getPriority
/*!
 * @brief Get priority
 * Returns the priority of the sensor
 * 
 * @param None
 * @return priority (int) The priority of the sensor
 */
int DigitalSensor::getPriority() const {
    return priority;
};