/*
 * BYU RACING
 * Authors    David Reinhardt
 * Goal: Read in digital signals using the 
 *       DigitalSensor class
 */

#include <Arduino.h>
#include "DigitalSensor.h"

#define SWITCH_PIN 20

DigitalSensor* flip;

void setup() {
  flip = new DigitalSensor(1, 500, SWITCH_PIN);

  Serial.begin(9600);
}

void loop() {
  if(flip->readyToCheck()){
    Serial.println(flip->readInputs());
  }
}
