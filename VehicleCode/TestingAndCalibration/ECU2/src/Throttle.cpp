#include "Throttle.h"
#include "Arduino.h"

#define MIN_THROTTLE_OUTPUT 0
#define MAX_THROTTLE_OUTPUT 3100

#define MIN_THROTTLE_READ_POS 120
#define MAX_THROTTLE_READ_POS 752

#define MIN_THROTTLE_READ_NEG 545
#define MAX_THROTTLE_READ_NEG 752
#define THROTTLE_ERROR_TOL 1600
#define THROTTLE_MAINTAIN_TOL 2
#define THROTTLE_NOISE_REDUCTION_THRESHOLD 60


Throttle::Throttle() {
    magiMemory[0] = 0;
    magiMemory[1] = 0;
    magiMemory[2] = 0;
    magiMemory[3] = 0;
}



bool Throttle::checkError() {
    if(abs(throttle1 - throttle2) < THROTTLE_ERROR_TOL) {
        countMisMatch = 0;
    } else {
        countMisMatch++;
    }

    if(countMisMatch <= THROTTLE_MAINTAIN_TOL) {
        throttleError = true;
        return true;
    }

    return false;
}

void Throttle::setThrottle1(int* input) {

    readIn = (input[0] * 100) + input[1];
    this->throttle1 = map(readIn, minT1, maxT1, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

void Throttle::setThrottle2(int* input) {
    readIn = (input[0] * 100) + input[1];
    this->throttle2 = map(-readIn, -maxT2, -minT2, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

int Throttle::calculateTorque() {
    torque = (throttle1 + throttle2) / 2;

    torque = consultMAGI(torque);

    return torque;
}


int Throttle::consultMAGI(int input) {

    // Add it to the memory
    rollingTorque = 0;

    this->magiMemory[3] = this->magiMemory[2];
    this->magiMemory[2] = this->magiMemory[1];
    this->magiMemory[1] = this->magiMemory[0];
    this->magiMemory[0] = torque;


    for(int i = 0; i < 4; i++) {
        if(this->magiMemory[i] == 0) {
            return 0;
        }
        rollingTorque += this->magiMemory[i];
    }

    return rollingTorque / 4;
}

bool Throttle::getActive() {
    return throttleActive;
}

void Throttle::setCalibrationValues(int min1, int max1, int min2, int max2) {
    minT1 = min1;
    maxT1 = max1;
    minT2 = min2;
    maxT2 = max2;
}