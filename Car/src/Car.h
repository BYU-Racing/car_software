#ifndef CAR_H
#define CAR_H
#include "State.h"
#include <typeinfo>
#include "IdleState.h"
#include "ActiveState.h"
#include "SensorData.h"

#define ID_SIZE 4
#define DATA_SIZE 8
#define TIMESTAMP_SIZE 8


struct Car {
    private:
        SensorData sensorData = SensorData();
        State state;
        //data for driving
        //TO DO inst in constructor
        bool inertiaShutdown;
        bool keyPosition;
        double acceleratorPedal;
        double brakePosition;

        int ledPin;
    public:
        Car() {};
        Car(int _ledPin) : state(IdleState(_ledPin)), ledPin(_ledPin), inertiaShutdown(true),
                        keyPosition(false), acceleratorPedal(0), brakePosition(0) {};
        void updateSensors(bool, bool);
        void updateState(SensorData sensorData);
        void updateDriveSensor(SensorData sensorData);
        void logData(SensorData sensorData);
        bool getInertiaShutdown()  { return inertiaShutdown; }
        bool getKeyPosition() { return keyPosition; }
};

void Car::updateSensors(bool _keyPosition, bool _inertiaShutdown) {
    //read in sensors
    //sensorData.setKeyPosition(_keyPosition);
    //sensorData.setInertiaShutdown(_inertiaShutdown);
    //updateState(sensorData);
}



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

    //push to sd card
}

#endif