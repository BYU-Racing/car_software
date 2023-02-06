#ifndef CAR_H
#define CAR_H
#include "IdleState.h"

class Car {
    private:
        State state;
        bool keyPosition;
        bool inertiaShutdown;

    public:
        Car(int _ledPin) : state(IdleState(*this, _ledPin)) {}
        void updateSensors(bool _keyPosition, bool _inertiaShutdown);
        void updateState();
        void logData();
        bool getInertiaShutdown()  {return inertiaShutdown;}
        bool getKeyPosition() {return keyPosition;}
        void changeState(State newState) {state = newState;}
        void race();
};

void Car::updateSensors(bool _keyPosition, bool _inertiaShutdown) {
    //read in sensors
    keyPosition = _keyPosition;
    inertiaShutdown = _inertiaShutdown;
    updateState();
}

void Car::updateState() {
    state.checkActive();

}

void Car::race() {
    state.race();
}

#endif