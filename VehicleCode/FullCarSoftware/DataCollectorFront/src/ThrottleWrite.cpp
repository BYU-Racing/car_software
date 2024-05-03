// #include <Arduino.h>
// #include <FlexCAN_T4.h>
// // #include "../include/ThrottleWrite.h"

// #define POT 24
// const float BIAS = 200;
// const float RANGE = 800 - BIAS;


// FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can1;

// // int speedCalc(int);

// int percentCalc1(double pot, double bias = 0);
// int getLow(int percent);
// int getHigh(int percent);
// int speedCalc(int pot);


// void setup() {
//   Serial.begin(9600);
//   Serial.println("Start");

//   // SET UP CAN
//   can1.begin();
//   can1.setBaudRate(250000);
// }

// void loop() {
//   int percent = percentCalc1(analogRead(POT),0);
//   Serial.print(percent);
//   int torqueLow = getHigh(200);
//   int torqueHigh = getHigh(200);
//   int speedLow = getLow(percent);
//   int speedHigh = getHigh(percent);

//   CAN_message_t msg;
//   msg.len=8;
//   msg.id=1;
//   msg.buf[0]=torqueLow;
//   msg.buf[1]=torqueHigh;
//   msg.buf[2]=speedLow;
//   msg.buf[3]=speedHigh;
//   msg.buf[4]=1;
//   msg.buf[5]=1;
//   msg.buf[6]=0;
//   msg.buf[7]=0;
//   msg.id=2;
//   can1.write(msg);
//   delay(300);
// }

// int percentCalc1(double pot, double bias = 0) {
//   double max = 1024;
//   double weight = 10000/max;
//   double percent = (max - pot + bias)* weight;
//   return static_cast<int>(percent);
//   // return percent;
// }

// int getLow(int percent) {
//   int low = percent%256;
//   return low;
// }

// int getHigh (int percent) {
//   int high = percent/256;
//   return high;
// }
