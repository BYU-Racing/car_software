#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"

#define POT1 24
#define POT2 25
#define ID1 1
#define ID2 2
const float BIAS = 200;
const float RANGE = 800 - BIAS;


FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

// int speedCalc(int);

int percentCalc(double, double, double);
int* buildData(int, int);
int getLow(int percent);
int getHigh(int percent);
int speedCalc(int pot);

// initialize throttle sensor
int throttleFreq = 10;
AnalogSensor throttle1 = AnalogSensor(ID1, throttleFreq, POT1);
AnalogSensor throttle2 = AnalogSensor(ID2, throttleFreq, POT2);


void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  // set up CAN
  can1.begin();
  can1.setBaudRate(250000);

}

void loop() {
  int percent1 = 0;
  int percent2 = 0;
  double bias = 0;
  const int torque = 200;
  if (throttle1.readyToCheck() && throttle2.readyToCheck()) {
    // read throttle sensor
    // percent1 = percentCalc(throttle1.readInputs(), bias, 1024);
    percent2 = percentCalc(throttle2.readInputs(), 93, 962);
    // Serial.print("Throttle 1: ");
    // Serial.println(percent1);
    Serial.print("Throttle 2: ");
    Serial.println(percent2);

    // if(abs(percent1 - percent2) < 25){
      int length = 8;

      int* sendData = buildData(torque, percent2);

      // send CAN message
      SensorData message = SensorData(ID1, sendData, length, millis());
      // message.toString();
      can1.write(message.formatCAN());
    // }
  }
  delay(1000);
}

int* buildData(int torque, int percent){
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

    return sendData;
}

int percentCalc(double pot, double bias, double max) {
  Serial.println(pot);
  double weight = 10000 / max;
  double percent = (pot + bias) * weight;
  return static_cast<int>(percent);
}

int getLow(int percent) {
  return percent % 256;
}

int getHigh(int percent) {
  return percent / 256;
}
