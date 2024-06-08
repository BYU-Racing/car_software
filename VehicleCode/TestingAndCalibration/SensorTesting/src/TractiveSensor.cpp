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
    

    //Send the motor read message
    // msg.id = 0x0C1;

    // msg.buf[0] = 141;
    // msg.buf[1] = 0;
    // msg.buf[2] = 0;
    // msg.buf[3] = 0;
    // msg.buf[4] = 0;
    // msg.buf[5] = 0;
    // msg.buf[6] = 0;
    // msg.buf[7] = 0;

    // can.write(msg);


    // previousUpdateTime = millis();
    // while(millis() - previousUpdateTime <= CHECK_TIME_MS) {
    //     if(can.read(rmsg)) {
    //         if(rmsg.id == 0x0C2) {
    //             return 1;
    //         }
    //     } 
    // }
    return 1;
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