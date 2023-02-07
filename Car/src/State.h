#ifndef STATE_H
#define STATE_H
#include "Car.h"

class State{
    protected:
        int ledPin;
    public:
        //Car car = NULL;
        //State(Car _car, int _ledPin) : car(_car), ledPin(_ledPin) {};
        virtual void checkActive();
        virtual void toggleBrakes();
        virtual void updateThrottle();
        void race();
};

void State::race() {
    //Car car = Car(2);
    //do some racing things here
}

#endif