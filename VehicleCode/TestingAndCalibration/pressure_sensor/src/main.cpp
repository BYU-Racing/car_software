#include <Arduino.h>

#define BRAKE A0
#define VREF 5
#define BITS 1023

float reading;

void setup() {
  pinMode(BRAKE, INPUT);

  Serial.begin(9600);
  delay(200);
  Serial.println("Starting!");
}

void loop() {
  reading = analogRead(BRAKE);
  
  Serial.println(reading / BITS * VREF);
  delay(200);
  
}
