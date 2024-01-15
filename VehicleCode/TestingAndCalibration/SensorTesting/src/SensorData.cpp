#include "SensorData.h"
#include <Arduino.h>
#include <FlexCAN_T4.h>

// TODO: add docstrings for each method

SensorData::SensorData() {
    id = 0;
    data = {0};
    timeStamp = 0;
    dataLength = 0;
}

SensorData::SensorData(int inId, int* inData, int dataLength, unsigned long inTimeStamp) {
    id = inId;
    data = inData;
    dataLength = 8;
    timeStamp = inTimeStamp;
}

// CHECK: Implement this method
SensorData::SensorData(CAN_message_t canMessage) {
    id = canMessage.id;
    timeStamp = canMessage.timestamp;
    dataLength = canMessage.len;
    data = new int[dataLength];
    for (int i = 0; i < dataLength; i++) {
        data[i] = canMessage.buf[i];
    }
}

// CHECK: Implement destructor
SensorData::~SensorData() {
    delete[] data;
}

int SensorData::getTimeStamp() const {
    return timeStamp;
}

int SensorData::getId() const {
    return id;
}

int* SensorData::getData() const {
    return data;
}

void SensorData::setId(int inId) {
    id = inId;
}

void SensorData::setData(int* inData) {
    data = inData;
}

// CHECK: Implement this method
void SensorData::setTimeStamp(unsigned long inTimeStamp) {
    timeStamp = inTimeStamp;
}

// TODO: Implement this method
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