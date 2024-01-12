#include "SensorData.h"
#include <Arduino.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

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
    dataLength = dataLength;
    timeStamp = inTimeStamp;
}

// CHECK: Implement this method
SensorData::SensorData(CAN_message_t canMessage) {
    id = canMessage.id;
    timeStamp = canMessage.timestamp;
    dataLength = canMessage.len;
    data = new int[dataLength];
    for (size_t i = 0; i < dataLength; i++) {
        data[i] = canMessage.buf[i];
    }
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
    for (size_t i = 0; i < dataLength; i++) {
        canMessage.buf[i] = data[i];
    }
    canMessage.len = dataLength;
    canMessage.timestamp = timeStamp;
    return canMessage;
}