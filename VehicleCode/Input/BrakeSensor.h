#ifndef BRAKESSENSOR_H
#define BRAKESENSOR_H

#include "Sensor.h"
#include "SensorData.h"
#include <Arduino.h>

class BrakeSensor : public Sensor {
    private:
    int baseline = 0;
    int errorMargin = 0;
    bool pressState = false;
    bool prevPressState = false;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
    
    void sendMotorCommand(bool pressState);




    
}