#include <Arduino.h>

void setup() {
  pinMode(19, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(19, HIGH);
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(19, LOW);
  digitalWrite(13, LOW);
}

void loop() {
  digitalWrite(19, HIGH);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(19, LOW);
  digitalWrite(13, LOW);
  delay(500);
}
