/*
 * BYU RACING
 * Authors    David Reinhardt
 * Goal: Receive signals from the CANBus to verify
 *       that the teensy and the wiring is correct
 */

// TEST
#include <Arduino.h>
#include <FlexCAN_T4.h>

CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

#define BAUD 250000
#define LED 13

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(BAUD);

  // SET UP LED
  pinMode(LED, OUTPUT);  
}

void loop() {
  if(can2.read(rmsg)) {
    Serial.println(rmsg.buf[0]);
    // write the value to the LED
    digitalWrite(LED, rmsg.buf[0]);
  }  
}
