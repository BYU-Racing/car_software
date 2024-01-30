#include "SensorData.h"
#include <Arduino.h>
#include <FlexCAN_T4.h>


/**
 * @brief Default constructor for SensorData class
 * 
 * Instructions to send an ERROR message:
 * inId = IDERROR = 0
 * inData = {sensorID, shutDown, errorType, **errorData}
 * inDataLength = 3 + errorDataLength
 * inTimeStamp = millis()
 * 
 * shutDown:
 *      0: No shutdown
 *      1: Shutdown
 * errorType:
 *      0: No Error
 *      1: Warning
 *      2: Critical
 *      3: Fatal
*/
SensorData::SensorData() {
    id = 0;
    data = {0};
    timeStamp = 0;
    dataLength = 0;
}

/**
 * @brief Constructor for SensorData class
 * 
 * @param inId (int) The unique identifier for the sensor.
 * @param inData (int*) The data from the sensor.
 * @param inDataLength (int) The length of the data array.
 * @param inTimeStamp (unsigned long) The timestamp of the data.
*/
SensorData::SensorData(int inId, int* inData, int inDataLength, unsigned long inTimeStamp) {
    id = inId;
    data = inData;
    dataLength = inDataLength;
    timeStamp = inTimeStamp;
}

// CHECK: Implement this method
/**
 * @brief CAN Constructor for SensorData class
 * 
 * @param canMessage (CAN_message_t) The CAN message to be converted to a SensorData.
 * Everything else is the same as the other constructor.
*/
SensorData::SensorData(CAN_message_t canMessage) {
    id = canMessage.id;
    timeStamp = canMessage.timestamp;
    dataLength = canMessage.len;
    data = new int[dataLength];
    for (int i = 0; i < dataLength; i++) {
        data[i] = canMessage.buf[i];
    }
}

/**
 * @brief Destructor for SensorData class
*/
SensorData::~SensorData() {
    delete[] data;
}


// Getters and Setters

int SensorData::getTimeStamp() const {
    return timeStamp;
}

int SensorData::getId() const {
    return id;
}

int* SensorData::getData() const {
    return data;
}

int SensorData::length() const {
    return dataLength;
}

void SensorData::setId(int inId) {
    id = inId;
}

void SensorData::setData(int* inData) {
    data = inData;
}

void SensorData::setTimeStamp(unsigned long inTimeStamp) {
    timeStamp = inTimeStamp;
}

// TODO: Implement this method
/**
 * @brief Format the SensorData into a CAN_message_t.
 * 
 * @return (CAN_message_t) The formmatted CAN message.
*/
CAN_message_t SensorData::formatCAN() const {
    CAN_message_t canMessage;
    canMessage.id = id;
    for (int i = 0; i < dataLength; i++) {
        canMessage.buf[i] = data[i];
    }
    canMessage.len = dataLength;
    canMessage.timestamp = timeStamp;
    return canMessage;
}

/**
 * @brief Print the SensorData to the Serial Monitor.
*/
void SensorData::toString() const {
    Serial.println("ID: " + String(id));
    Serial.println("Timestamp: " + String(timeStamp));
    Serial.println("Data Length: " + String(dataLength));
    Serial.print("Data: ");
    for (int i = 0; i < dataLength; i++) {
        Serial.print(data[i]);
        Serial.print(" ");
    }
    Serial.println();
}