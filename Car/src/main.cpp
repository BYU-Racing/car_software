#ifndef MAIN_CPP
#define MAIN_CPP
#include <Arduino.h>
#include "Car.h"
#include "State.h"

#define KEYSWITCH 2
#define INERTIASWITCH 3
#define LED 4

Car car;

void setup() {
  pinMode(KEYSWITCH, INPUT);
  pinMode(INERTIASWITCH, INPUT);
  pinMode(LED, OUTPUT);
  car = Car(LED);
}

void loop() {

  //read can signals
  //canSniff();

}

void canSniff() {
  SensorData sensorData;
  //determine which sensor it came from
    //drive sensors
      //call updateDriveSensor
    //data logging sensors
      car.logData(sensorData);
}

#endif