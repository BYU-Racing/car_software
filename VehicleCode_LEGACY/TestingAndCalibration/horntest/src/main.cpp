#include <Arduino.h>

void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void loop() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(500);
}
