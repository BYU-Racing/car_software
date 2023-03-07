/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Receive a Signal over CAN and turn on an LED
 */
#include <Arduino.h>
#include <FlexCAN_T4.h>

#define LED 2
#define CAN_BAUDRATE 9600

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

CAN_message_t msg;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  while(!Serial); // wait for Serial to open
  Serial.println("CAN LED Receiver");
  Can0.begin();
  Can0.setBaudRate(CAN_BAUDRATE);
}

void loop() {
  int nRead = Can0.read(msg);
  Serial.printf("%d\n", nRead);
  if (nRead != 0) {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
  }
}