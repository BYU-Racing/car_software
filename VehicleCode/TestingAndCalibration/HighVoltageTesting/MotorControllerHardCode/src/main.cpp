/*
 * BYU RACING
 * Authors    Landon Wheeler
 * Goal: Send the default CAN message to the motor controller for debugging
 */

#include <Arduino.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);

}

void loop() {

  // CREATE AND SEND THE DEFAULT MOTORCONTROLLER CAN MESSAGE
  CAN_message_t msg;
  msg.len=8;
  msg.buf[0]=44;
  msg.buf[1]=1;
  msg.buf[2]=244;
  msg.buf[3]=1;
  msg.buf[4]=0;
  msg.buf[5]=1;
  msg.buf[6]=0;
  msg.buf[7]=0;
  msg.id=192;
  can2.write(msg);
  Serial.println("sent");

  delay(10);
}