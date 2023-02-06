#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
#include "State.h"

class ActiveState: public State {
    public:
        ActiveState(Car newCar, int _ledPin) : State(newCar, _ledPin) {};
        void checkActive();
        void toggleBrakes();
        void updateThrottle();
        void race();
};
void ActiveState::checkActive() {
    if(car.getInertiaShutdown() || car.getKeyPosition()) {
        car.changeState(IdleState(car));
    }
}

void ActiveState::race() {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
}

#endif