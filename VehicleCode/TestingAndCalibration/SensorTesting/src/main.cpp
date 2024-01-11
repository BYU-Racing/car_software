// #include <Arduino.h>
// #include <AnalogSensor.h>
// #define S_PIN 5

// // put function declarations here:
// AnalogSensor Poten(1, 1, 1, A4);

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(S_PIN, INPUT);
//   Serial.begin(9600);
//   Poten.setPin(A4);
//   Poten.setWaitTime(100);
// }

// void loop() {
//   // put your main code here, to run repeatedly:

//   if(Poten.readyToCheck()) {
//     int val = Poten.readInputs();
//     Serial.println(val);
//   }

// }

#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"
// #include "../include/ThrottleWrite.h"

#define POT 24
const float BIAS = 200;
const float RANGE = 800 - BIAS;


FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

// int speedCalc(int);

int percentCalc1(double pot, double bias = 0);
int getLow(int percent);
int getHigh(int percent);
int speedCalc(int pot);

// initialize throttle sensor
int throttleID = 1;
int throttleFreq = 10;
int throttlePrio = 1;
int throttlePin = POT;
AnalogSensor throttle = AnalogSensor(throttleID, throttleFreq, throttlePrio, throttlePin);


void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can1.begin();
  can1.setBaudRate(250000);

}

void loop() {
  int percent = 0;
  double bias = 0;
  const int torque = 200;
  if (throttle.readyToCheck()) {
    // read throttle sensor
    percent = percentCalc1(throttle.readInputs(), bias);
    Serial.println(percent/100);

    // convert to motor controller format
    int torqueLow = getLow(torque);
    int torqueHigh = getHigh(torque);
    int speedLow = getLow(percent);
    int speedHigh = getHigh(percent);

    // construct formatted data
    int length = 8;
    int* sendData = new int[length];
    sendData[0] = torqueLow;
    sendData[1] = torqueHigh;
    sendData[2] = speedLow;
    sendData[3] = speedHigh;
    sendData[4] = 1;
    sendData[5] = 1;
    sendData[6] = 0;
    sendData[7] = 0;

    // send CAN message
    SensorData message = SensorData(throttleID, throttlePrio, sendData, length, millis());
    can1.write(message.formatCAN());
  }

}

int percentCalc1(double pot, double bias=0) {
  double max = 1024;
  double weight = 10000 / max;
  double percent = (max - pot + bias) * weight;
  return static_cast<int>(percent);
}

int getLow(int percent) {
  return percent % 256;
}

int getHigh(int percent) {
  return percent / 256;
}
