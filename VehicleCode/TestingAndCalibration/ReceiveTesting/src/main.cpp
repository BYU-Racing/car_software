#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <string>
#include "AnalogSensor.h"
#include "Sensor.h"
#include "SensorData.h"
#include "DataCollector.h"
#include "ThrottleSensor.h"
#include "Car.h"


// throttle sensor variables
#define POT1 24
#define POT2 25
#define ID_ERROR 0
#define THROTTLE_POT 192
#define WHEEL_SPEED_FL 5
#define BIAS1 0
#define MAX1 1024

// CAN message variables
#define LENGTH 8
#define BEGIN 9600      // 9,600
#define BAUDRATE 250000 // 250,000
#define DELAYBY 0


// initialize can and throttle sensor
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
int throttleFreq = 20;
int numSensors = 1;
ThrottleSensor throttle = ThrottleSensor(THROTTLE_POT, throttleFreq, POT1, POT2, BIAS1, MAX1, LENGTH);
// AnalogSensor tireSpeed1 = AnalogSensor(WHEEL_SPEED_FL, 1, 26, 0, 100, 1);
Sensor* sensors[] = {&throttle};
DataCollector collector = DataCollector(sensors, numSensors, millis());
Car car;



// MAIN -------------------------------------------------------------------------------------------

void setup() {
    Serial.begin(BEGIN);
    Serial.println("Start");

    // set up CAN
    can1.begin();
    can1.setBaudRate(BAUDRATE);

    // set up collector and car
    collector.setCAN(can1);
    collector.resetTimeZero(millis());
    car.createNewCSV();
    car.setCAN(can1);
    delay(2000);
}


void loop() {
    collector.checkSensors();
    car.readSensors();
    delay(DELAYBY);
}
