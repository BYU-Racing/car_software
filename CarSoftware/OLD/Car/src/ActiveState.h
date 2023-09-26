#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
#include "State.h"

class ActiveState: public State {
    public:
        ActiveState(int _ledPin) : State(_ledPin) {};
        int checkState(bool inertiaShutdown, bool keyPosition, double acceleratorPedal, double brakePosition);
        //void toggleBrakes();
        void race();
};

int ActiveState::checkState(bool inertiaShutdown, bool keyPosition, double acceleratorPedal, double brakePosition) {
    if(inertiaShutdown || !keyPosition) {
       return IDLE;
    }
}

void ActiveState::race() {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
}

#endif