#include <Arduino.h>
#include <Dashboard.h>
#include "EasyNextionLibrary.h"
#include "FlexCAN_T4.h"

#define BEGIN 9600
#define BAUDRATE 250000

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

EasyNex myDisplay(Serial2);

void trigger0();
void trigger1();

int ThrottleHandoff;
CAN_message_t msg;

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
  //Read throttle1 and throttle2 and send the MIN command to the ECU

  ThrottleHandoff = myDisplay.readNumber("PreRun.Throttle1Val.val");

  msg.id=201;

  msg.len=8;

  msg.buf[0]=(ThrottleHandoff / 100);
  msg.buf[1]=(ThrottleHandoff - ((ThrottleHandoff / 100) * 100);


  ThrottleHandoff = myDisplay.readNumber("PreRun.Throttle2.val");

  msg.buf[2]=(ThrottleHandoff / 100);
  msg.buf[3]=(ThrottleHandoff - ((ThrottleHandoff / 100) * 100));


  can2.write(msg);
}

void trigger1() {
  //Read throttle1 and throttle2 and send the MIN command to the ECU

  ThrottleHandoff = myDisplay.readNumber("PreRun.Throttle1Val.val");

  msg.id=202;

  msg.len=8;

  msg.buf[0]=(ThrottleHandoff / 100);
  msg.buf[1]=(ThrottleHandoff - ((ThrottleHandoff / 100) * 100);


  ThrottleHandoff = myDisplay.readNumber("PreRun.Throttle2.val");

  msg.buf[2]=(ThrottleHandoff / 100);
  msg.buf[3]=(ThrottleHandoff - ((ThrottleHandoff / 100) * 100));


  can2.write(msg);
}