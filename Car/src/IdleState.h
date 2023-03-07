#ifndef IDLESTATE_H
#define IDLESTATE_H
#include <Arduino.h>
//#include "ActiveState.h"
#include "State.h"
#include "SensorData.h"

class IdleState: public State {
    public:
        IdleState() {};
        IdleState(int _ledPin) : State(_ledPin) {};
        int checkState(SensorData);
        //void toggleBrakes();
        //void updateThrottle();
        void race();
};

int IdleState::checkState(SensorData sensorData) {
    if(!sensorData.getInertiaShutdown() && sensorData.getKeyPosition()) {
        return ACTIVE;
    }
    return IDLE;
    // key is changed to on in some place
}

void IdleState::race() {
    Serial.println("Idle");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}

#endif