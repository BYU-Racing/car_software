#include <Arduino.h>
#include "ECU.h"

constexpr int BEGIN = 9600;
constexpr int BAUDRATE = 250000;

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
ECU mainECU = ECU();

void setup() {
  Serial.begin(BEGIN);
  Serial.println("Start");

  // set up CAN
  can1.begin();
  can1.setBaudRate(BAUDRATE);

  can2.begin();
  can2.setBaudRate(BAUDRATE);

  mainECU.setCAN(can2, can1);

  mainECU.boot();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  mainECU.run();
}
