/*
 * BYU RACING
 * Authors    David Reinhardt
 * Goal: Send signals on the CANBus to verify that
 *       the teensy and the wiring is correct
 */

#include <Arduino.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

bool state;

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);

  state = LOW;
}

void loop() {
  // flip the states value
  state = !state;

  // CREATE AND SEND THE CAN MESSAGE
  CAN_message_t msg;
  msg.len=1;
  msg.buf[0]=state;
  msg.id=2;
  can2.write(msg);
  Serial.println("sent");

  delay(500);
}
