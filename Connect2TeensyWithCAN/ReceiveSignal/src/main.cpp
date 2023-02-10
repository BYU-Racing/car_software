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

// IF THE FIRST BIT OF THE MESSAGE IS ZERO TURN LIGHT OFF, IF IT IS ONE TURN LIGHT ON
void canSniff2(const CAN_message_t &msg) {
  boolean msgVal = msg.buf[0];
  if(msgVal) {
      digitalWrite(LED, HIGH);
  } else {
      digitalWrite(LED, LOW);
  }
  char* buf = (char*) msg.buf;
  Serial.print(buf);
}

void setup() {
  //SETUP LED PIN
  pinMode(LED, OUTPUT);
  pinMode(23, OUTPUT);
  //digitalWrite(LED, HIGH);

  //TODO: SETUP CANBUS PINS
  receiver.begin();
  receiver.setClock(CLK_60MHz);
  receiver.setBaudRate(95238);
  receiver.mailboxStatus();
  receiver.setMaxMB(1);
  receiver.onReceive(canSniff);

  //TODO: WRITE TO SERIAL MONITOR
  Serial.begin(95238);
  Serial.println("hello");
}

int i = 0;

void loop() {

  if (receiver.read(msg)) {
      canSniff(msg);
      delay(1000);
      Serial.println("received!");
  }
  
  delay(300);

  /*if(i == 0) {
    digitalWrite(LED, HIGH);
    Serial.print("Hello World\n");
    Serial.flush();
    i++;
  }*/



}