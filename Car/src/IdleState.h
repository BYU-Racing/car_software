#ifndef IDLESTATE_H
#define IDLESTATE_H
#include <Arduino.h>
#include "ActiveState.h"

class IdleState: public State {
    public:
        IdleState() {}
        IdleState(Car newCar, int _ledPin) : State(newCar, _ledPin) {};
        void checkActive();
        void toggleBrakes();
        void updateThrottle();
        void race();
};

void IdleState::checkActive() {
    if(!car.getInertiaShutdown() && car.getKeyPosition()) {
        car.changeState(ActiveState(car));
    }
    // key is changed to on in some place
}

void IdleState::race() {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}

#endif