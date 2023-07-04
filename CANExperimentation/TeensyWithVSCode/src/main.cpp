/*
 * Created by David Reinhardt
 * First Code to be uploaded to one of our Teensys
 * Goal: Blink an LED and write to the serial Monitor
 */

#include <Arduino.h>

#define LED 2

void setup() {
  //SETUP THE LED PIN
  pinMode(LED, OUTPUT);

  //TURNON SERIAL MONITOR
  Serial.begin(9600);

}

void loop() {
  //TURN ON THE LED FOR HALF A SECOND AND WRITE ON TO SERIAL MONITOR
  digitalWrite(LED, HIGH);
  Serial.println("On");
  delay(500);

  //TURN OFF THE LED FOR HALF A SECOND AND WRITE OFF TO SERIAL MONITOR
  digitalWrite(LED, LOW);
  Serial.println("Off");
  delay(500);
}