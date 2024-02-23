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
  delay(100);
  Serial.println(state);
}

void loop() {
  if(millis() - prevTime > DELAY){
    state = !state;
    prevTime = millis();
    Serial.println(state);
    digitalWrite(LED, state);
  }
}
