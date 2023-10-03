#include "SensorData.h"

SensorData::SensorData() {
    id = 0;
    priority = 0;
    data = {0};
    timeStamp = 0;
}

SensorData::SensorData(int inId, int inPriority, int* inData, int inTimeStamp) {
    id = inId;
    priority = inPriority;
    data = inData;
    timeStamp = inTimeStamp;
}

SensorData::SensorData(int canMessage) {
    //Need can message template to know where to find each attribute
}

int SensorData::getTimeStamp() const {
    return timeStamp;
}

int SensorData::getId() const {
    return id;
}

int SensorData::getPriority() const {
    return priority;
}

int* SensorData::getData() const {
    return data;
}

void SensorData::setId(int inId) {
    id = inId;
}

void SensorData::setPriority(int inPriority) {
    priority = inPriority;
}

void SensorData::setData(int* inData) {
    data = inData;
}

std::string SensorData::formatCAN() const {
    return "";
}