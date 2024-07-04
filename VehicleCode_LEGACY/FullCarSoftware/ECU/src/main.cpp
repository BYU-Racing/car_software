#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <string>

#include "Car.h"

// CAN message variables
#define LENGTH 8
#define BEGIN 9600          // 9,600
#define BAUDRATE 250000     // 250,000
#define SAVE_DELAY 20000    // 20,000 ms
#define DELAYBY 0

#define TESTING 0

// initialize can, car, and horn
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
Car car;

// MAIN -------------------------------------------------------------------------------------------

void setup() {
    Serial.begin(BEGIN);
    Serial.println("Start");

    // set up CAN
    can1.begin();
    can1.setBaudRate(BAUDRATE);

    // set up car
    car.initialize(can1, SAVE_DELAY);
    pinMode(12, OUTPUT);

    // visibility control
    if (TESTING == 1) {
        Serial.println("Waiting 5 seconds to start.");
        delay(2000); // so that you can read the file name at the start
        Serial.println("ALERT:");
        Serial.print("SD card saves every ");
        Serial.print(SAVE_DELAY / 1000);
        Serial.println(" seconds.");
        Serial.print("LOOP delay set to ");
        Serial.print(DELAYBY);
        Serial.println(" ms.");
        Serial.println("Reading on CAN2.");
        Serial.println("Starting.");
        //car.setLogState(true);
    }
}


void loop() {
    car.readSensors();
    delay(DELAYBY);
}
