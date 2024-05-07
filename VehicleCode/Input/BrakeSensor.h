#ifndef BRAKESENSOR_H
#define BRAKESENSOR_H

#include "Sensor.h"
#include "SensorData.h"
#include <Arduino.h>

class BrakeSensor : public Sensor {
    private:
    int baseline;
    int errorMargin;
    bool pressState;
    bool prevPressState;
    bool driveState;
    bool inError;
    bool inCriticalError;
    int brakeP;
    int* sendData;
    int dataLength;
    int timeErrorStart;
    int errorBaseline;
    int lastTorqueCommand;
    int maxTorque;
    
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
    
    void sendMotorCommand();



    public:
    BrakeSensor(int id, int waitTime, int inPin, int dataLength, int baseline, int errorMargin);
    //GetID

    int readInputs() override;
    bool readyToCheck();
    int rescale(int data) override;

    int* buildData(int value) override;

    int* buildError() override;

    int getId() override;

    int getDataLength() override;

    void setCan(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIn);

    void setDriveState();

    bool checkError(int value);

    void sendStopCommand();

    void sendStartCommand();

    void setLastTorque();

    
};


#endif