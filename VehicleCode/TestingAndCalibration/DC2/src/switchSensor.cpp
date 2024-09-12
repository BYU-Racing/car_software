#include "switchSensor.h"
#include <Arduino.h>


SwitchSensor::SwitchSensor(int id, int time, int pin, bool inCritical) {
    this->sensorID = id;
    this->waitTime = time;
    this->inputPins[0] = pin;
    pinMode(pin, INPUT_PULLDOWN);
    this->isCritical = inCritical;
    this->SwitchVal = 0;
}


int SwitchSensor::readInputs() {
    this->previousUpdateTime = millis();
    this->runner = 0;
    this->ticker = 0;


    while(millis() - this->previousUpdateTime <= 2) {
        
        this->ticker = this->ticker + digitalRead(this->inputPins[0]);

        this->runner++;
    }

    this->comparitor = this->ticker / this->runner;

    if(this->comparitor >= 0.87) {
        Serial.print("Switch: ");
        Serial.println("1");
        return 1;

    } else {
        Serial.print("Switch: ");
        Serial.println("0");
        return 0;
    }

    // return digitalRead(this->inputPins[0]);
}

/*! 
 * @brief Get ID
 * Returns the ID of the sensor
 * 
 * @param None
 * @return sensorID (int) The ID of the sensor
 */
int SwitchSensor::getId(){
    return sensorID;
};


/*! 
 * @brief Get input pin
 * Returns the pin that the sensor is connected to
 * 
 * @param None
 * @return input pin (int) The pin of the sensor
 */
int SwitchSensor::getPins(){
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
int SwitchSensor::getWaitTime(){
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
int SwitchSensor::getDataLength(){
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
int* SwitchSensor::buildData(int value) {
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
int* SwitchSensor::buildError() {
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
int SwitchSensor::rescale(int data) {
    //Transform data
    return -1;
};

bool SwitchSensor::readyToCheck() {
    return (waitTime <= int(millis() - previousUpdateTime));
}

bool SwitchSensor::getCritical() {
    return isCritical;
}

bool SwitchSensor::plugTest() {
    return (analogRead(inputPins[0]) == 0);
}


