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
#define IDERROR 0
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
#define errorDataLength 7
#define shutDown 1
#define noShutDown 0
#define noError 0
#define warning 1
#define critical 2
#define fatal 3

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
int input1 = 0;
int input2 = 0;
const int torque = 200;
int countMismatch = 0;

// initialize throttle sensor
int throttleFreq = 10;
AnalogSensor throttle1 = AnalogSensor(ID1, throttleFreq, POT1);
AnalogSensor throttle2 = AnalogSensor(ID2, throttleFreq, POT2);



// MAIN -------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  // set up CAN
  can1.begin();
  can1.setBaudRate(250000);
}


void loop() {
 
  if (throttle1.readyToCheck() && throttle2.readyToCheck()) {
    // read throttle sensor
    input1 = throttle1.readInputs();
    input2 = throttle2.readInputs();
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
    int* sendData = new int[length];
    if (abs(percent1 - percent2) < errorTol) {
      countMismatch = 0;
    }
    else {
      countMismatch++;
      Serial.print("^ throttle mismatch ^ = ");
      Serial.println(countMismatch);
    }

    // build normal CAN message
    bool errorFound = false;
    if (countMismatch <= maintainTol) {
      sendData = buildData(torque, percent1);
    }
    // build 0 value CAN message
    else if (countMismatch < shutdownTol) {
      sendData = buildData(0, 0);
      sendError(sendData, noShutDown, warning);
    }
    // build error CAN message
    else {
      errorFound = true;
      sendError(sendData, shutDown, fatal);
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



// HELPER FUNCTIONS -------------------------------------------------------------------------------

/**
 * @brief Builds the data array for the CAN message.
 * 
 * @param torque (int) The torque value to be sent.
 * @param percent (int) The percent value to be sent.
 * 
 * @return (int*) The data array for the CAN message.
*/
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


/**
 * @brief Sends an error message.
 * 
 * @param sendData (int*) The data array for the CAN message.
 * @param command (int) The command to be sent.
 *                          0: No shutdown
 *                          1: Shutdown
 * @param errorType (int) The type of error.
 *                          0: No Error
 *                          1: Warning
 *                          2: Critical
 *                          3: Fatal
*/
void sendError(int* sendData, int command, int errorType) {
    sendData[0] = ID1;
    sendData[1] = command;
    sendData[2] = errorType;
    sendData[3] = input1;
    sendData[4] = input2;
    sendData[5] = percent1;
    sendData[6] = percent2;
    SensorData message = SensorData(IDERROR, sendData, errorDataLength, millis());
    can1.write(message.formatCAN());
}


/**
 * @brief Gets the low byte of a percent value.
 * 
 * @param percent (int) The percent value to be converted.
 * 
 * @return (int) The low byte of the percent value.
*/
int getLow(int percent) {
  return percent % byteSize;
}


/**
 * @brief Gets the high byte of a percent value.
 * 
 * @param percent (int) The percent value to be converted.
 * 
 * @return (int) The high byte of the percent value.
*/
int getHigh(int percent) {
  return percent / byteSize;
}
