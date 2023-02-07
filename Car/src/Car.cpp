#ifndef CAR_CPP
#define CAR_CPP
#include "Car.h"

void Car::updateSensors(bool _keyPosition, bool _inertiaShutdown) {
    //read in sensors
    keyPosition = _keyPosition;
    inertiaShutdown = _inertiaShutdown;
    updateState();
}

void Car::updateState() {
    //state.checkActive();

}

void Car::race() {
    //state.race();
}

#endif