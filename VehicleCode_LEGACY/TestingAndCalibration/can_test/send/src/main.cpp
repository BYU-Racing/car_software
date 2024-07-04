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
int* sendData;
#define LENGTH 8
CAN_message_t msg;

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);

  state = LOW;
  sendData = new int[LENGTH];
}

void loop() {
  // flip the states value
  state = !state;

  // CREATE AND SEND THE CAN MESSAGE
  sendData[0] = 44; //torqueLow
  sendData[1] = 1; //torqueHigh
  sendData[2] = 244; //speedLow
  sendData[3] = 1; //speedHigh
  sendData[4] = 1;
  sendData[5] = 1;
  sendData[6] = 0;
  sendData[7] = 0;
  msg.len=LENGTH;
  for (int i = 0; i < LENGTH; i++) {
    msg.buf[i] = sendData[i];
  }
  msg.id=192;
  can2.write(msg);
  Serial.println("sent");

  // delay(0);
}
