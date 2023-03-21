#ifndef CAR_H
#define CAR_H
#include "State.h"
#include <typeinfo>
#include <SPI.h>
#include <SD.h>
#include "IdleState.h"
#include "ActiveState.h"
#include "SensorData.h"



#define ID_SIZE 4
#define DATA_SIZE 4
#define TIMESTAMP_SIZE 4 //32 bits or 4 bytes 



struct Car {
    private:
        SensorData sensorData = SensorData();
        State state;
        //data for driving
        bool inertiaShutdown;
        bool keyPosition;
        double acceleratorPedal;
        double brakePosition;

        int ledPin;

        File dataLog;
    public:
        Car() {};
        Car(int _ledPin, File _dataLog) : state(IdleState(_ledPin)), ledPin(_ledPin), inertiaShutdown(true),
                        keyPosition(false), acceleratorPedal(0), brakePosition(0), dataLog(_dataLog) {};
        void updateState(SensorData sensorData);
        void updateDriveSensor(SensorData sensorData);
        void logData(SensorData sensorData);
        bool getInertiaShutdown()  { return inertiaShutdown; }
        bool getKeyPosition() { return keyPosition; }
};



void Car::updateDriveSensor(SensorData sensorData) {
    switch(sensorData.sensorid) {
        case INERTIA_SWITCH:
            inertiaShutdown = sensorData.data;
            break;
        case KEY_SWITCH:
            keyPosition = sensorData.data;
            break;
        case ACCEL_PEDAL:
            acceleratorPedal = sensorData.data;
            break;
        case BRAKE_PEDAL:
            brakePosition = sensorData.data;
            break;
    }
    int newState = state.checkState(inertiaShutdown, keyPosition, acceleratorPedal, brakePosition);
    switch(newState) {
        case ACTIVE:
            if(typeid(state) != typeid(ActiveState())) {
                state = ActiveState(0);
            }
            break;
        case IDLE:
            if(typeid(state) != typeid(IdleState())) {
                state = IdleState(0);
            }
            break;
    }
}



void Car::logData(SensorData sensorData) {
    unsigned char buf[ID_SIZE + DATA_SIZE + TIMESTAMP_SIZE];
    memcpy(&buf[0], &sensorData.sensorid, ID_SIZE);
    memcpy(&buf[ID_SIZE], &sensorData.data, DATA_SIZE);
    memcpy(&buf[ID_SIZE + DATA_SIZE], &sensorData.timestamp, TIMESTAMP_SIZE);

    //Serial.write(buf, ID_SIZE + DATA_SIZE + TIMESTAMP_SIZE);

    //push to sd card
    dataLog = SD.open("data.csv", FILE_WRITE);

    dataLog.write(buf, ID_SIZE + DATA_SIZE + TIMESTAMP_SIZE);
    dataLog.println(""); //add a new line between data
    dataLog.close();
}

#endif