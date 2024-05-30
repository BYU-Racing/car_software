#include "TractiveSensor.h"
#include <Arduino.h>

#define CHECK_TIME_MS 6

TractiveSensor::TractiveSensor(int id, int waitTime) {
    sensorID = id;
    this->waitTime = waitTime;
}


void TractiveSensor::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIN) {
    can = canIN;
}

int TractiveSensor::readInputs() {
    previousUpdateTime = millis();

    //Use the BMS IDs
    //THIS CHECKS FOR 6 MILLISECONDS!!!!!!!

    while(millis() - previousUpdateTime <= CHECK_TIME_MS) {
        if(can.read(rmsg)) {
            if(rmsg.id == 37 || rmsg.id == 38) {
                return 1;
            }
        } 
    }
    return 0;
}

bool TractiveSensor::readyToCheck() {
    return (waitTime <= int(millis() - previousUpdateTime));
}

int* TractiveSensor::buildData(int value) {

    return new int[2]{0, value};
}

int* TractiveSensor::buildError() {
    return new int[1]{0};
}

int TractiveSensor::rescale(int data) {
    return data;
}

int TractiveSensor::getId() {
    return sensorID;
}

int TractiveSensor::getWaitTime() {
    return waitTime;
}

int TractiveSensor::getDataLength() {
    return 1;
}