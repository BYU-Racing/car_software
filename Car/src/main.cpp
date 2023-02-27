#ifndef MAIN_CPP
#define MAIN_CPP
#include <Arduino.h>
#include "Car.h"

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
  // put your main code here, to run repeatedly:
  car.updateSensors(digitalRead(KEYSWITCH), digitalRead(INERTIASWITCH));

  car.race();
}

#endif