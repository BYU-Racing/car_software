#include <Arduino.h>
#include <AnalogSensor.h>
#define S_PIN 5

// put function declarations here:
AnalogSensor Poten(1, 1, 1, A4);

void setup() {
  // put your setup code here, to run once:
  pinMode(S_PIN, INPUT);
  Serial.begin(9600);
  Poten.setPin(A4);
  Poten.setWaitTime(100);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Poten.readyToCheck()) {
    int val = Poten.readInputs();
    Serial.println(val);
  }

}
