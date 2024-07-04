#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <string>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"
#include "Error.h"
#include "DataCollector.h"
#include "ThrottleSensor.h"


// throttle sensor variables
#define POT1 24
#define POT2 25
#define ID_ERROR 0
#define THROTTLE_POT 192
#define WHEEL_SPEED_FL 5
#define BIAS1 0
#define BIAS2 0
#define MAX1 1024
#define MAX2 1000

// error variables
#define ERROR_TOL 1000
#define MAINTAIN_TOL 2
#define ERRORDATALENGTH 7
#define SHUTDOWN 1
#define NO_SHUTDOWN 0
#define WARNING 1
#define CRITICAL 2
#define FATAL 3

// CAN message variables
#define LENGTH 8
#define DELAYBY 10
#define BEGIN 9600      // 9,600
#define BAUDRATE 250000 // 250,000


// HELPER FUNCTIONS
// int percentCalc(double, double, double);
int* buildData(int, int);
int getLow(int);
int getHigh(int);
void sendError(int*, int, int);


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
int numSensors = 1;
ThrottleSensor throttle = ThrottleSensor(THROTTLE_POT, throttleFreq, POT1, POT2, BIAS1, MAX1, LENGTH);
AnalogSensor tireSpeed1 = AnalogSensor(WHEEL_SPEED_FL, 1, 26, 0, 100, 1);
Sensor* sensors[] = {&throttle};
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
 
  // if (throttle1.readyToCheck() && throttle2.readyToCheck()) {
  //   // read throttle sensor
    
    // percent1 = throttle1.readInputs();
  //   percent2 = throttle2.readInputs();
  //   // percent1 = map(input1, BIAS1, MAX1, 0, MAX_PERCENT);
  //   // percent2 = map(input2, BIAS2, MAX2, 0, MAX_PERCENT);

  //   // print throttle values
    // Serial.print("  Input  1: ");
    // Serial.print(input1);
  //   Serial.print(" | 2: ");
  //   Serial.println(input2);
  //   // Serial.print("Throttle 1: ");
  //   // Serial.print(percent1);
  //   // Serial.print(" | 2: ");
  //   // Serial.println(percent2);

  //   // check for mismatch
  //   int* sendData = new int[LENGTH];
  //   if (abs(percent1 - percent2) < ERROR_TOL) {
  //     countMismatch = 0;
  //   }
  //   else {
  //     countMismatch++;
  //     Serial.print("\t\t\t << throttle mismatch ^ = ");
  //     Serial.println(countMismatch);
  //   }

  //   // build normal CAN message
  //   bool errorFound = false;
  //   if (countMismatch <= MAINTAIN_TOL) {
  //     sendData = throttle1.buildData(torque, percent1);
  //   }
  //   // build 0 value CAN message
  //   else {
  //     sendData = throttle1.buildData(0, 0);
  //   }
    
  //   // send CAN message
  //   if (!errorFound) {
  //     SensorData message = SensorData(ACCELERATOR_POT_1, sendData, LENGTH, millis());
  //     can1.write(message.formatCAN());
  //   }
  //   // delete sendData;

  // }
  delay(DELAYBY);
}



// HELPER FUNCTIONS -------------------------------------------------------------------------------




// /**
//  * @brief Sends an error message.
//  * 
//  * @param sendData (int*) The data array for the CAN message.
//  * @param command (int) The command to be sent.
//  *                          0: No shutdown
//  *                          1: Shutdown
//  * @param errorType (int) The type of error.
//  *                          0: No Error
//  *                          1: Warning
//  *                          2: Critical
//  *                          3: Fatal
// */
// void sendError(int* sendData, int command, int errorType) {
//     sendData[0] = ACCELERATOR_POT_1;
//     sendData[1] = command;
//     sendData[2] = errorType;
//     sendData[3] = input1;
//     sendData[4] = input2;
//     sendData[5] = percent1;
//     sendData[6] = percent2;
//     SensorData message = SensorData(ID_ERROR, sendData, ERRORDATALENGTH, millis());
//     can1.write(message.formatCAN());
// }
