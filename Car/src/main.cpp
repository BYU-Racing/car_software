#ifndef MAIN_CPP
#define MAIN_CPP
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include "Car.h"
#include "State.h"

#define KEYSWITCH 2
#define INERTIASWITCH 3
#define LED 4

File dataLog;
const int chipSelect = BUILTIN_SDCARD;

const String fileName = "data.txt";

Car car;

void canSniff() {
  SensorData sensorData;
  sensorData.sensorid = INERTIA_SWITCH;
  sensorData.data = 0x123456;
  sensorData.timestamp = millis();
  //determine which sensor it came from
    //drive sensors
      //call updateDriveSensor
    //data logging sensors
      car.logData(sensorData);
}

void setup() {
  pinMode(KEYSWITCH, INPUT);
  pinMode(INERTIASWITCH, INPUT);
  pinMode(LED, OUTPUT);
  car = Car(LED, dataLog);

  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  //SD.remove("data.txt");
  dataLog = SD.open("data.txt", FILE_WRITE);
  dataLog.print("\r\n\r\n");
  dataLog.close();
  }
}

void loop() {

  //read can signals
  if (digitalRead(KEYSWITCH)) {
    Serial.println("reading");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    canSniff();
  }
}



#endif