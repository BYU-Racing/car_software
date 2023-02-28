/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Receive a Signal over CAN and turn on an LED
 */
#include <Arduino.h>
#include <FlexCAN_T4.h>

#define LED 2
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> receiver;
CAN_message_t msg;

// FLASHES LIGHT 3 TIMES WHEN A SIGNAL IS RECEIVED
void canSniff(const CAN_message_t &msg) {
  for(int i = 0; i < 3; i++){
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

void setup() {
  //SETUP LED PIN
  pinMode(LED, OUTPUT);
  pinMode(23, OUTPUT);
  //digitalWrite(LED, HIGH);

  //SETUP CANBUS PINS
  receiver.begin();
  receiver.setClock(CLK_60MHz);
  receiver.setBaudRate(9600);
  receiver.setMaxMB(1);
  receiver.setMB(MB0, RX,EXT);
  receiver.onReceive(MB0, canSniff);

  //WRITE TO SERIAL MONITOR
  Serial.begin(9600);
  while(!Serial);
  receiver.mailboxStatus();
  Serial.println("Hello");
}

void loop() {

  if (receiver.read(msg)) {
      canSniff(msg);
      delay(1000);
      Serial.println("received!");
  }

  receiver.mailboxStatus();
  delay(800);

}