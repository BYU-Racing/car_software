#ifndef STATE_H
#define STATE_H
#include "Car.h"

class State{
    protected:
        int ledPin;
        Car car;
    public:
        State() {};
        State(Car _car, int _ledPin) : car(_car), ledPin(_ledPin) {};
        virtual void checkActive();
        virtual void toggleBrakes();
        virtual void updateThrottle();
        void race();
};

void State::race() {
    //do some racing things here
}

#endif