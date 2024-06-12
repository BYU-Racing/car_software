/*
* BYU RACING
* Authors David Reinhardt
* Goal: Receive signals from the CANBus
*/

#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SensorData.h"
#include <set>

CAN_message_t rmsg;
CAN_message_t msg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

#define BAUD 250000
#define LED 13

unsigned long last_print;
std::set<int> settyBoi;

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(BAUD);

  // SET UP LED
  pinMode(LED, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {
  digitalWrite(12, LOW);
  if(can2.read(rmsg)) {
    if(rmsg.id == 222) {
      Serial.print("ID: ");
      Serial.print(rmsg.id);
      Serial.print("  DATA: ");
      for ( uint8_t i = 0; i < rmsg.len; i++ ) {
        Serial.print(rmsg.buf[i], HEX); Serial.print(" ");
      } Serial.println();
    }

  
  }
}