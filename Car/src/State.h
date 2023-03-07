#ifndef STATE_H
#define STATE_H
#include "Car.h"
#include "SensorData.h"

#define IDLE 0
#define ACTIVE 1

class State{
    protected:
        int ledPin;
    public:
        State() {};
        State(int _ledPin) : ledPin(_ledPin) {};
        virtual int checkState(SensorData sensorData);
        //virtual void toggleBrakes();
        //virtual void updateThrottle();
        void race();
        
};

void State::race() {
    Serial.println("state");
    //do some racing things here
}

int State::checkState(SensorData sensorData) {
    return 0;
}

#endif