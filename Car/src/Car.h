#ifndef CAR_H
#define CAR_H
#include "State.h"
#include "IdleState.h"
#include "SensorData.h"

struct Car {
    private:
        SensorData sensorData = SensorData();
        State state;
    public:
        Car() {};
        Car(int _ledPin) : state(IdleState(_ledPin)) {};
        void updateSensors(SensorData _sensorData);
        void updateState(SensorData sensorData);
        void logData();
        bool getInertiaShutdown()  { return sensorData.getInertiaShutdown(); }
        bool getKeyPosition() { return sensorData.getKeyPosition(); }
        void run();
};

void Car::updateSensors(SensorData _sensorData) {
    //read in sensors
    this->sensorData = sensorData;
    updateState(sensorData);
}

void Car::updateState(SensorData sensorData) {
    state.checkState(sensorData);
}

void Car::run() {
    //update sensors
    //check state
    //do racing
    state.race();
}

#endif