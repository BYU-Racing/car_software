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
        virtual int checkState(bool inertiaShutdown, bool keyPosition, double acceleratorPedal, double brakePosition);
        void race();
        
};

void State::race() {
    //do some racing things here
}

int State::checkState(bool inertiaShutdown, bool keyPosition, double acceleratorPedal, double brakePosition) {
    return 0;
}

#endif