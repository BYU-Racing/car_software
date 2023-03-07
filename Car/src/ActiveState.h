#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
#include "State.h"

class ActiveState: private State {
    public:
        ActiveState(int _ledPin) : State(_ledPin) {};
        int checkState(SensorData sensorData);
        void toggleBrakes();
        void updateThrottle();
        void race();
};

int ActiveState::checkState(SensorData sensorData) {
    if(sensorData.getInertiaShutdown() || sensorData.getKeyPosition()) {
       return IDLE;
    }
}

void ActiveState::race() {
    Serial.println("Active");
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
}

#endif