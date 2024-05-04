#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <string>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"
#include "Error.h"
#include "DataCollector.h"
#include "ThrottleSensor.h"
#include "BrakeSensor.h"
#include "DigitalSensor.h"


// throttle sensor variables
#define POT1 24
#define POT2 25
#define ID_ERROR 0
#define THROTTLE_POT 192
#define WHEEL_SPEED_FL 5
#define BIAS1 512
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
#define DELAYBY 30
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
int throttleFreq = 30;
int numSensors = 4;
int damperID = 12;
int damperFreq = 75;
int damperPin = 17;


int brakeID = 11;
int brakeFreq = 50;
int brakePin = 20;
int brakeLength = 2;
int baseline = 40;
int errorMargin = 22;

int switchID = 15;
int switchTime = 100;


ThrottleSensor throttle = ThrottleSensor(THROTTLE_POT, throttleFreq, POT1, POT2, BIAS1, MAX1, LENGTH);
AnalogSensor damperPot1 = AnalogSensor(damperID, damperFreq, damperPin);
BrakeSensor myBrake = BrakeSensor(brakeID, brakeFreq, brakePin, brakeLength, baseline, errorMargin);

DigitalSensor startSwitch = DigitalSensor(switchID, switchTime, 37);

Sensor* sensors[] = {&throttle, &damperPot1, &myBrake, &startSwitch};
DataCollector collector = DataCollector(sensors, numSensors, millis(), true);



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

  collector.setBrakeSensor(&myBrake);
}


void loop() {

  collector.checkSensors();

}
