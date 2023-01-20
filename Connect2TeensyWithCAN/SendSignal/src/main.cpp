/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Send a Signal over CAN when a button is pressed
 */

#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <isotp.h>

#define BUTTON 2
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> sender;
isotp<RX_BANKS_16, 512> tp;


void setup() {
  //SETUP BUTTON PIN
  pinMode(BUTTON, OUTPUT);

  //SETUP CANBUS PINS
  sender.begin();
  sender.setClock(CLK_60MHz);
  sender.setBaudRate(95238);
  sender.setMaxMB(16);
}

void loop() {
  if(digitalRead(BUTTON)){
    ISOTP_data config;
;
  }
}