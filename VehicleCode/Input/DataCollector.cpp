#include "DataCollector.h"
// #include <Arduino.h>
// #include <FlexCAN_T4.h>

// Global variables
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
const int BAUDRATE = 250000;


// CHECK define function
// Constructor
DataCollector::DataCollector(Sensor** sensors, int numSensors, unsigned long startTime) {
    this->sensors = sensors;
    this->numSensors = numSensors;
    this->timeZero = startTime;
    // can2 attribute
}


// CHECK define function
/*!
 * @brief Check each sensor for new data
 * 
 * Determines whether each sensor is ready to send data. If so, it calls the
 * readData method for that sensor.
 * 
 * @param None
 * 
 * @return None
 */ 
void DataCollector::checkSensors() {
    for (int i = 0; i < numSensors; i++) {
        // Check if the sensor is ready to send more data
        if (sensors[i]->readyToCheck()) {
            readData(sensors[i]);
        }
    }
}


// CHECK define function
/*!
 * @brief Read data from sensors
 * 
 * Reads data from a sensor, then builds a SensorData object for each piece of
 * data and sends it over CAN with the sendSignal method.
 * 
 * @param sensor (Sensor*) A pointer to a Sensor object
 * 
 * @return None
 */
// 
void DataCollector::readData(Sensor* sensor) {
    // Call the readInputs method to obtain an array of ints
    int* rawData = sensor->readInputs();
    int sensorID = sensor->getId();
    int priority = sensor->getPriority();
    unsigned long timestamp = millis() - timeZero;

    // Create a new sensor data object for each int in the array
    // TODO readInputs must always return an array of ints that ends with -1
    // just do size
    int i = 0;
    while (rawData[i] != -1) {
        SensorData* sensorData = new SensorData(sensorID, priority, rawData[i], timestamp);
        try {
            sendSignal(sensorData);
        } catch (...) {
            delete sensorData;
        }
        delete sensorData;
        i++;
    }
}


// CHECK define function idk what I'm doing here
/*!
 * @brief Send data to Car and Dashboard objects
 * 
 * Initializes the CAN bus, then sends a CAN message to the Car and Dashboard
 * using sensorData's formatCAN method.
 * 
 * @param sensorData (SensorData*) A pointer to a SensorData object
 * 
 * @return None
 */
void DataCollector::sendSignal(SensorData* sensorData) {
    // Create a CAN message
    CAN_message_t canMessage = sensorData->formatCAN();
    can2.write(canMessage);

    // // Create a CAN message
    // std::string canMessage = sensorData->formatCAN();
    // CAN_message_t msg;

    // // Fill the buffer with the message
    // uint8_t messageLength = static_cast<uint8_t>(canMessage.length());
    // if (messageLength <= sizeof(msg.buf)) {
    //     // Copy characters from the string into the buffer
    //     for (uint8_t i = 0; i < messageLength; i++) {
    //         msg.buf[i] = canMessage[i];
    //     }
    // } else {
    //     for (uint8_t i = 0; i < sizeof(msg.buf); i++) {
    //         msg.buf[i] = 0;
    //     }
    // }

    // // Set the message length and id and send the message
    // msg.len = messageLength;
    // // TODO set msg.id to sensor id or priority
    // msg.id = 2;
    // can2.write(msg);
}
