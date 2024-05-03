#ifndef SCREEN_H
#define SCREEN_H

#include "Actuator.h"
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>


class Screen : public Actuator {
private:
    // Additional attributes specific to Screen
    int* pins;
    int numPins;
    int mode;
    int pauseTime;
    unsigned long modeTimeStart;
    Adafruit_7segment matrix;
    unsigned long timeStartTime;

public:
    // Constructor
    Screen();

    // Destructor

    // Override the writeToDisplay method
    void updateValue(const SensorData& data);

    // Additional methods for Screen

    void displayTime();
    void displayLapTime(int inSeconds, int milliseconds);
    void setMatrix(Adafruit_7segment myMatrix);
};

#endif // SCREEN_H