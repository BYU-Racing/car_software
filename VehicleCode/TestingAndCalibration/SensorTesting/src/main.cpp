#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <string>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"
#include "Error.h"


// throttle sensor variables
#define POT1 24
#define POT2 25
#define ID1 1
#define ID2 2
#define bias1 0
#define bias2 0
#define max1 1024
#define max2 1000
#define maxPercent 10000

// error variables
#define errorTol 400
#define maintainTol 1
#define shutdownTol 10

// CAN message variables
#define length 8
#define byteSize 256
#define delayBy 500


// HELPER FUNCTIONS
// int percentCalc(double, double, double);
int* buildData(int, int);
int getLow(int);
int getHigh(int);


// initialize data processing variables
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
int percent1 = 0;
int percent2 = 0;
const int torque = 200;
int countMismatch = 0;

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
 
  // read throttle sensor
  if (throttle1.readyToCheck() && throttle2.readyToCheck()) {
    // percent1 = percentCalc(throttle1.readInputs(), bias1, 1024);
    // percent2 = percentCalc(throttle2.readInputs(), 0, 300);
    int input1 = throttle1.readInputs();
    int input2 = throttle2.readInputs();
    percent1 = map(input1, bias1, max1, 0, maxPercent);
    percent2 = map(input2, bias2, max2, 0, maxPercent);

    // print throttle values
    Serial.print("  Input  1: ");
    Serial.print(input1);
    Serial.print(" | 2: ");
    Serial.println(input2);
    Serial.print("Throttle 1: ");
    Serial.print(percent1);
    Serial.print(" | 2: ");
    Serial.println(percent2);

    // check for mismatch
    if (abs(percent1 - percent2) < errorTol) {
      countMismatch = 0;
    }
    else {
      // TODO send warning
      countMismatch++;
      Serial.print("^ throttle mismatch ^ = ");
      Serial.println(countMismatch);
    }

    // build normal CAN message
    int* sendData = new int[length];
    bool errorFound = false;
    if (countMismatch <= maintainTol) {
      sendData = buildData(torque, percent1);
    }
    // build 0 value CAN message
    else if (countMismatch < shutdownTol) {
      sendData = buildData(0, 0);
      // int errorLevel = 1;
      // int errLength = 2
      // int* mismatch = new int[errLength]{ percent1, percent2 };
      // std::string errorMessage = "throttle mismatch";
      
      // Error message = Error(ID1, mismatch, errLength, millis(), "Throttle", errorLevel, errorMessage, false);
      // can1.write(message.formatCAN());
      // delete[] mismatch;
    }
    
    // TODO figure out how to send the error over can or otherwise communicate with Car
    else {
      errorFound = true;
      // int errorLevel = 3;
      // int errLength = 2
      // int* mismatch = new int[errLength]{ percent1, percent2 };
      // std::string errorMessage = "throttle mismatch for over 100 ms";
      
      // Error message = Error(ID1, mismatch, errLength, millis(), "Throttle", errorLevel, errorMessage, true);
      // can1.write(message.formatCAN());
      // delete[] mismatch;
    }
    
    // send CAN message
    if (!errorFound) {
      SensorData message = SensorData(ID1, sendData, length, millis());
      can1.write(message.formatCAN());
    }
    delete[] sendData;

  }
  delay(delayBy);
}


// HELPER FUNCTIONS

int* buildData(int torque, int percent){
    // convert to motor controller format
    int torqueLow = getLow(torque);
    int torqueHigh = getHigh(torque);
    int speedLow = getLow(percent);
    int speedHigh = getHigh(percent);

    // construct formatted data
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

// this got replaced by map()
// int percentCalc(double pot, double bias, double max) {
//   // Serial.println(pot);
//   double weight = 10000 / max;
//   double percent = (pot + bias) * weight;
//   return static_cast<int>(percent);
// }

int getLow(int percent) {
  return percent % byteSize;
}

int getHigh(int percent) {
  return percent / byteSize;
}
