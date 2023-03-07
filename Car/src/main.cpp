#ifndef MAIN_CPP
#define MAIN_CPP
#include <Arduino.h>
#include "Car.h"
#include "State.h"

#define KEYSWITCH 3
#define INERTIASWITCH 4
#define LED 2

Car car;
SensorData sensorData;

void setup() {

  Serial.begin(9600);
  while(!Serial);
  Serial.println("Hello");

  pinMode(KEYSWITCH, INPUT);
  pinMode(INERTIASWITCH, INPUT);
  pinMode(LED, OUTPUT);
  car = Car(LED);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorData.setKeyPosition(digitalRead(KEYSWITCH));
  sensorData.setInertiaShutdown(digitalRead(INERTIASWITCH));

  car.updateSensors(sensorData);
  
  car.run();
}

#endif