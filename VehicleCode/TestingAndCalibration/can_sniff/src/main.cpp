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

  for(int i = 0; i <= 0b11111111111111111111111111111; ++i){
    msg.id = i;
    msg.flags.extended = 1;
    msg.buf[0] = 0b00110100;
    can2.write(msg);
    if(can2.read(rmsg)) {
      Serial.println(rmsg.id, HEX);
      settyBoi.insert(rmsg.id);
    }
    delay(.1);
  }
}

void loop() {
  // if(can2.read(rmsg)) {
  //   last_print = millis();
  //   Serial.println(rmsg.id, HEX);
  //   for ( uint8_t i = 0; i < rmsg.len; i++ ) {
  //     Serial.print(rmsg.buf[i], HEX); Serial.print(" ");
  //   } Serial.println();

  //   if(rmsg.id == 0x1CECFFF4){
  //     delay(500);
  //   }
  // }

  // msg.id = 0x18EF00F4;
  // msg.flags.extended = 1;
  // msg.buf[0] = 0b00110100;
  // can2.write(msg);
  // Serial.println("Sent!");
  // delay(300);

  for(int id: settyBoi){
    Serial.println(id);
  }
}