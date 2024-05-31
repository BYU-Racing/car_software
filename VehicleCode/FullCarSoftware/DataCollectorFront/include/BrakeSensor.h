#ifndef BRAKESENSOR_H
#define BRAKESENSOR_H

#include "Sensor.h"
#include "SensorData.h"
#include <Arduino.h>

class BrakeSensor : public Sensor {
    private:
    int baseline;
    int errorMargin;
    bool pressState = false;
    bool prevPressState = false;
    bool driveState = false;
    bool inError = false;
    bool inCriticalError = false;
    int brakeP = 0;
    int* sendData = new int[8];
    int dataLength;
    int timeErrorStart;
    int errorBaseline;
    int lastTorqueCommand = 0;
    int maxTorque = 2000;
    CAN_message_t msg;
    
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

    void setLastTorque(int lastCommand);

    
};


#endif