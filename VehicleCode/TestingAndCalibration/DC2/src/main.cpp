#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <DataCollector.h>
#include <DigitalSensor.h>
#include <AnalogSensor.h>
#include <Sensor.h>


FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

#define THROTTLE_1_ID 1
#define THROTTLE_1_WAIT 10
#define THROTTLE_1_PIN 10

#define THROTTLE_2_ID 2
#define THROTTLE_2_WAIT 10
#define THROTTLE_2_PIN 11

#define BRAKE_ID 3
#define BRAKE_WAIT 10
#define BRAKE_PIN 12

#define SWITCH_ID 4
#define SWITCH_WAIT 10
#define SWITCH_PIN 13


AnalogSensor throttle1 = AnalogSensor(THROTTLE_1_ID, THROTTLE_1_WAIT, THROTTLE_1_PIN, true);
AnalogSensor throttle2 = AnalogSensor(THROTTLE_2_ID, THROTTLE_2_WAIT, THROTTLE_2_PIN, true);
AnalogSensor brake = AnalogSensor(BRAKE_ID, BRAKE_WAIT, BRAKE_PIN, true);

DigitalSensor startSwitch = DigitalSensor(SWITCH_ID, SWITCH_WAIT, SWITCH_PIN, true);

#define NUM_SENSORS 4

Sensor* sensors[] = {&throttle1, &throttle2, &brake, &startSwitch};

DataCollector collector = DataCollector(sensors, NUM_SENSORS, millis());

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("START");

  can2.begin();
  can2.setBaudRate(250000);

  collector.setCAN(can2);
  collector.resetTimeZero(millis());
  
}

void loop() {
  // put your main code here, to run repeatedly:
  collector.checkSensors();
  delay(100);
}
