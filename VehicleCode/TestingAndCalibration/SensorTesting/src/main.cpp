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


void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can1.begin();
  can1.setBaudRate(250000);
}

void loop() {
  int percent = percentCalc1(analogRead(POT),0);
  Serial.println(percent/100);
  int torqueLow = getLow(200);
  Serial.print("Torque Low: ");
  Serial.println(torqueLow);
  int torqueHigh = getHigh(200);
  Serial.print("Torque High: ");
  Serial.println(torqueHigh);
  int speedLow = getLow(percent);
  Serial.print("Speed Low: ");
  Serial.println(speedLow);
  int speedHigh = getHigh(percent);
  Serial.print("Speed High: ");
  Serial.println(speedHigh);
  Serial.println();

  CAN_message_t msg;
  msg.len=8;
  msg.id=1;
  msg.buf[0]=torqueLow;
  msg.buf[1]=torqueHigh;
  msg.buf[2]=speedLow;
  msg.buf[3]=speedHigh;
  msg.buf[4]=1;
  msg.buf[5]=1;
  msg.buf[6]=0;
  msg.buf[7]=0;
  msg.id=2;
  can1.write(msg);
  delay(200);
}

int percentCalc1(double pot, double bias = 0) {
  double max = 1024;
  double weight = 10000/max;
  double percent = (max - pot + bias)* weight;
  return static_cast<int>(percent);
  // return percent;
}

int getLow(int percent) {
  int low = percent%256;
  return low;
}

int getHigh(int percent) {
  int high = percent/256;
  return high;
}
