#include <Arduino.h>

#define PIN1 39
#define PIN2 40

void setup() {
  pinMode(PIN1, INPUT);
  pinMode(PIN2, INPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(PIN1));
  Serial.println(analogRead(PIN2));
  Serial.println();
  delay(500);  
}
