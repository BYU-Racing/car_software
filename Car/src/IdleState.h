#ifndef IDLESTATE_H
#define IDLESTATE_H
#include <Arduino.h>
#include "State.h"
#include "SensorData.h"

class IdleState: public State {
    public:
        IdleState() {};
        IdleState(int _ledPin) : State(_ledPin) {};
        int checkState(bool inertiaShutdown, bool keyPosition, double acceleratorPedal, double brakePosition);
        void race();
};

int IdleState::checkState(bool inertiaShutdown, bool keyPosition, double acceleratorPedal, double brakePosition) {
    if(!inertiaShutdown && keyPosition) {
        return ACTIVE;
    }
    return IDLE;
    // key is changed to on in some place
}

void IdleState::race() {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}

#endif