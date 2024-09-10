#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <DataCollector.h>
#include <DigitalSensor.h>
#include <AnalogSensor.h>
#include <switchSensor.h>
#include <Sensor.h>


FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

constexpr int THROTTLE_1_ID = 3;
constexpr int THROTTLE_1_WAIT = 10;
constexpr int THROTTLE_1_PIN = 39;

constexpr int THROTTLE_2_ID = 4;
constexpr int THROTTLE_2_WAIT = 10;
constexpr int THROTTLE_2_PIN = 40;

constexpr int BRAKE_ID = 2;
constexpr int BRAKE_WAIT = 10;
constexpr int BRAKE_PIN = 21;

constexpr int SWITCH_ID = 1;
constexpr int SWITCH_WAIT = 10;
constexpr int SWITCH_PIN = 38;


AnalogSensor throttle1 = AnalogSensor(THROTTLE_1_ID, THROTTLE_1_WAIT, THROTTLE_1_PIN, true);
AnalogSensor throttle2 = AnalogSensor(THROTTLE_2_ID, THROTTLE_2_WAIT, THROTTLE_2_PIN, true);
AnalogSensor brake = AnalogSensor(BRAKE_ID, BRAKE_WAIT, BRAKE_PIN, true);

SwitchSensor startSwitch = SwitchSensor(SWITCH_ID, SWITCH_WAIT, SWITCH_PIN, true);

constexpr int NUM_SENSORS = 4;

Sensor* sensors[] = {&throttle1, &throttle2, &brake, &startSwitch};

DataCollector collector = DataCollector(sensors, NUM_SENSORS, millis());

//We need to see if the debounced switch sensor is required

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("START");

  can2.begin();
  can2.setBaudRate(250000);

  collector.setCAN(can2);
  collector.resetTimeZero(millis());

  pinMode(SWITCH_PIN, INPUT_PULLDOWN);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  collector.checkSensors();
}
