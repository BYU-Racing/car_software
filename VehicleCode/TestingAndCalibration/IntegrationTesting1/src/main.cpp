#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <string>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"
#include "Error.h"
#include "DataCollector.h"
#include "ThrottleSensor.h"
#include "DigitalSensor.h"


// throttle sensor variables
#define POT1 24
#define POT2 25
// #define POTB 29
#define ID_ERROR 0
#define THROTTLE_POT 1
#define WHEEL_SPEED_FL 5
#define BRAKE_PIN 29
#define BRAKE_ID 6
#define BUTTON_PIN 28
#define BUTTON_ID 7
#define BUTTON 2
#define BIAS1 0
#define MAX1 1024
#define testPOT 27


// CAN message variables
#define LENGTH 8
#define BEGIN 9600      // 9,600
#define BAUDRATE 250000 // 250,000
#define DELAYBY 0



// initialize throttle sensor
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
int brakeFreq = 100;
int buttonFreq = 100;
int numSensors = 3;
// ThrottleSensor throttle = ThrottleSensor(THROTTLE_POT, throttleFreq, POT1, POT2, BIAS1, MAX1, LENGTH);
AnalogSensor brakePressure = AnalogSensor(BRAKE_ID, brakeFreq, BRAKE_PIN, 0, 1024, 1);
AnalogSensor testPOT1 = AnalogSensor(13,100,testPOT, 0, 1024, 1);
DigitalSensor button = DigitalSensor(BUTTON_ID, buttonFreq, BUTTON_PIN);
Sensor* sensors[] = {&button, &brakePressure, &testPOT1};
DataCollector collector = DataCollector(sensors, numSensors, millis());



// MAIN -------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(BEGIN);
  Serial.println("Start");

  // set up CAN
  can1.begin();
  can1.setBaudRate(BAUDRATE);

  // TEST: I think this should be here but idk if it will cause a problem
  collector.setCAN(can1);
  collector.resetTimeZero(millis());
}


void loop() {

  collector.checkSensors();
 
  delay(DELAYBY);
}
