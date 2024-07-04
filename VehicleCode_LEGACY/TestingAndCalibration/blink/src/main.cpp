/*
 * BYU RACING
 * Authors    David Reinhardt
 * Goal: blink the onboard LED to verify that the
 *       teensy is functioning
 */

#include <Arduino.h>

#define LED 13 // built-in LED pin
#define DELAY 1000 // milliseconds
#define BAUD 9600

unsigned long prevTime;
bool state;

void setup() {
  prevTime = millis();
  state = LOW;

  // setup led pin
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, state); 

  // setup serial monitor
  Serial.begin(BAUD);
  delay(1000);
  Serial.println(state);
}

void loop() {
  // every delay time switch the state of the LED
  if(millis() - prevTime > DELAY){
    state = !state;
    prevTime = millis();
    Serial.println(state);
    digitalWrite(LED, state);
  }
}
