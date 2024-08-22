#include "Throttle.h"
#include "Arduino.h"

#define MIN_THROTTLE_OUTPUT 0
#define MAX_THROTTLE_OUTPUT 3100

#define MIN_THROTTLE_READ_POS 120
#define MAX_THROTTLE_READ_POS 752

#define MIN_THROTTLE_READ_NEG 545
#define MAX_THROTTLE_READ_NEG 752
#define THROTTLE_ERROR_TOL 1600
#define THROTTLE_MAINTAIN_TOL 20
#define THROTTLE_NOISE_REDUCTION_THRESHOLD 60


Throttle::Throttle() {
    magiMemory[0] = 0;
    magiMemory[1] = 0;
    magiMemory[2] = 0;
    magiMemory[3] = 0;
}



int Throttle::checkError() {
    if(abs(throttle1 - throttle2) < THROTTLE_ERROR_TOL) {
        countMisMatch = 0;
    } else {
        countMisMatch++;
    }

    if(countMisMatch >= THROTTLE_MAINTAIN_TOL) {
        throttleError = true;
        Serial.println("MISMATCH");
        return 1;
    }

    if(readIn1 == 0 || readIn2 == 0) {
        throttleError = true;
        Serial.println("0 THROTTLE THROWN");
        return 2;
    }

    return 0;
}

void Throttle::setThrottle1(int* input) {

    readIn1 = (input[0] * 100) + input[1];

    this->throttle1 = map(readIn1, minT1, maxT1, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

void Throttle::setThrottle2(int* input) {
    readIn2 = (input[0] * 100) + input[1];

    this->throttle2 = map(-readIn2, -maxT2, -minT2, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
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

void Throttle::setCalibrationValueMin(int min1, int min2) {
    maxT2 = min2;
    minT1 = min1;
}


void Throttle::setCalibrationValueMax(int max1, int max2) {
    minT2 = max2;
    maxT1 = max1;
}