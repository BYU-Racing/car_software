#ifndef TRACTIVESENSOR_H
#define TRACTIVESENSOR_H

#include "Sensor.h"
#include "SensorData.h"
#include <Arduino.h>

class TractiveSensor : public Sensor {
private:
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can;
    unsigned long lastSignal;
    int gap;
    bool tractiveActive;
    CAN_message_t rmsg;
    CAN_message_t msg;
    int waitTime;



public:


    TractiveSensor(int id, int waitTime);

    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIN);

    int readInputs() override;
    bool readyToCheck() override;
    int rescale(int data) override;
    int* buildData(int value) override;
    int* buildError() override;
    int getDataLength() override;

    int getId();
    int getWaitTime();
};

#endif