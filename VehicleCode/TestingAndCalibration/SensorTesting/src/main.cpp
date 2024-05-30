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
#include "TractiveSensor.h"


// throttle sensor variables
#define POT1_PIN 39
#define POT2_PIN 40
#define ID_ERROR 0
#define THROTTLE_POT_ID 192
#define BIAS1 36
#define BIAS2 679
#define MAX1 169
#define MAX2 907
#define THROTTLE_WAIT 30

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
#define DELAYBY 0
#define BEGIN 9600
#define BAUDRATE 250000


// initialize CAN variable
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

// damper variables
#define DAMPER_R_ID 12
#define DAMPER_R_PIN 22
#define DAMPER_L_ID 13
#define DAMPER_L_PIN 23
#define DAMPER_WAIT 100

// brake variables
#define BRAKE_ID 11
#define BRAKE_WAIT 30
#define BRAKE_PIN 21
#define BRAKE_LENGTH 2
#define BRAKE_BIAS 101
#define BRAKE_TOLERANCE 22

// switch variables
#define SWITCH_ID 15
#define SWITCH_WAIT 100
#define SWITCH_PIN 38

//TRACTIVE SENSOR VARS
#define TRACTIVE_ID 30
#define TRACTIVE_WAIT 100

// Declare sensor variables
ThrottleSensor throttle = ThrottleSensor(THROTTLE_POT_ID, THROTTLE_WAIT, POT1_PIN, 
                                         POT2_PIN, BIAS1, MAX1, BIAS2, MAX2, LENGTH);
AnalogSensor rightDamperPot = AnalogSensor(DAMPER_R_ID, DAMPER_WAIT, DAMPER_R_PIN);
AnalogSensor leftDamperPot = AnalogSensor(DAMPER_L_ID, DAMPER_WAIT, DAMPER_L_PIN);
BrakeSensor myBrake = BrakeSensor(BRAKE_ID, BRAKE_WAIT, BRAKE_PIN, BRAKE_LENGTH, 
                                  BRAKE_BIAS, BRAKE_TOLERANCE);

TractiveSensor BMSLover = TractiveSensor(TRACTIVE_ID, TRACTIVE_WAIT);

DigitalSensor startSwitch = DigitalSensor(SWITCH_ID, SWITCH_WAIT, SWITCH_PIN);

// data collector variables
#define NUM_SENSORS 6
Sensor* sensors[] = {&throttle, &rightDamperPot, &leftDamperPot, 
                     &myBrake, &startSwitch, &BMSLover};
DataCollector collector = DataCollector(sensors, NUM_SENSORS, millis(), true);


// MAIN -------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(BEGIN);
  Serial.println("Start");

  // set up CAN
  can1.begin();
  can1.setBaudRate(BAUDRATE);

  collector.setCAN(can1);
  collector.resetTimeZero(millis());

  collector.setBrakeSensor(&myBrake);
}


void loop() {

  collector.checkSensors();

  delay(DELAYBY);

}
