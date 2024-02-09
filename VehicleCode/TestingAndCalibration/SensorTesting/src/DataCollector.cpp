#include "DataCollector.h"
// #include <Arduino.h>
// #include <FlexCAN_T4.h>

// Global variables
#define BAUDRATE 250000
#define TORQUE_DEFAULT 200


// TEST: define function
/*!
 * @brief Constructor
 * Initializes the CAN bus and the sensors
 * 
 * @param sensors (Sensor**) An array of pointers to Sensor objects
 * @param numSensors (int) The number of sensors in the array
 * @param startTime (unsigned long) The time the car started
 * @return None
 */
DataCollector::DataCollector(Sensor** sensors, int numSensors, unsigned long startTime) {
    this->sensors = sensors;
    this->numSensors = numSensors;
    this->timeZero = startTime;
}



// TEST: define function
/*!
 * @brief Check each sensor for new data
 * Determines whether each sensor is ready to send data. If so, it calls the
 * readData method for that sensor.
 * 
 * @param None
 * @return None
 */ 
void DataCollector::checkSensors() {
    Serial.println("checking sensors");
    for (int i = 0; i < numSensors; i++) {
        // Check if the sensor is ready to send more data
        if (sensors[i]->readyToCheck()) {
            Serial.println("Sensors ready");
            readData(sensors[i]);
        }
    }
}


// TEST define function
/*!
 * @brief Read data from sensors
 * Reads data from a sensor, then builds a SensorData object for each piece of
 * data and sends it over CAN with the sendSignal method.
 * 
 * @param sensor (Sensor*) A pointer to a Sensor object
 * @return None
 */
void DataCollector::readData(Sensor* sensor) {
    // Call the readInputs method to obtain an array of ints
    int sensorID = sensor->getId();
    int rawData = sensor->readInputs();
    Serial.println(rawData);
    int dataLength = sensor->getDataLength();
    unsigned long timestamp = millis() - timeZero;
    
    int* sendData;
    if (rawData != -1) {
        sendData = sensor->buildData(rawData);
    } else {
        sendData = sensor->buildError();
    }

    // Create a new sensor data object for each int in the array
    SensorData sensorData = SensorData(sensorID, sendData, dataLength, timestamp);
    sendSignal(&sensorData);
}


// TEST: define function
/*!
 * @brief Send data to Car and Dashboard objects
 * Initializes the CAN bus, then sends a CAN message to the Car and Dashboard
 * using sensorData's formatCAN method.
 * 
 * @param sensorData (SensorData*) A pointer to a SensorData object
 * @return None
 */
void DataCollector::sendSignal(SensorData* sensorData) {
    // Create a CAN message
    can2.write(sensorData->formatCAN());
}

/**
 * @brief Set the CAN bus
 * @param can2 (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
void DataCollector::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2) {
    this->can2 = can2;
}


/**
 * @brief Reset the time zero
 * @param startTime (unsigned long) The time the car started
 */
void DataCollector::resetTimeZero(unsigned long startTime) {
    timeZero = startTime;
}