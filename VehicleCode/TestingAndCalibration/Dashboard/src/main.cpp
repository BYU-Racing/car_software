#include <Arduino.h>
#include <Dashboard.h>
#include "EasyNextionLibrary.h"
#include "FlexCAN_T4.h"

#define BEGIN 9600
#define BAUDRATE 250000

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

EasyNex myDisplay(Serial1);

void trigger0();
void trigger1();

Dashboard myDash;

void setup() {
  Serial.begin(9600);
  myDisplay.begin(9600);


  myDash.setDisplay(&myDisplay);


  can1.begin();
  can2.begin();

  can1.setBaudRate(BAUDRATE);
  can2.setBaudRate(BAUDRATE);

  myDash.setCAN(can2);
}

void loop() {
  myDash.updateDisplay();
  myDisplay.NextionListen();
}


void trigger0() {
  //Read throttle

  
}