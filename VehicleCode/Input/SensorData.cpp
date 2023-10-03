#include "SensorData.h"

SensorData::SensorData() {
    //Default Constructor
}

SensorData::SensorData(int inId, int inPriority, int* inData, int inTimeStamp) {
    //Constructor 1
    id = inId;
    priority = inPriority;
    data = inData;
    timeStamp = inTimeStamp;
}

SensorData::SensorData(int canMessage) {
    //CAN MESSAGE
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
    return {0};
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