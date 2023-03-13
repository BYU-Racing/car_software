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
#define POWER 3
#define LED 4
#define ID 0x00

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> sender;
// isotp<RX_BANKS_16, 512> tp;


void setup() {
  //Setup Serial Monitor
  Serial.begin(9600);
  while(!Serial);

  //SETUP BUTTON PIN
  pinMode(BUTTON, INPUT);

  //SETUP LED PIN
  pinMode(LED, OUTPUT);

  //SETUP POWER RAIL
  pinMode(POWER, OUTPUT);

  //SETUP CANBUS PINS
  sender.begin();
  sender.setClock(CLK_60MHz);
  sender.setBaudRate(9600);
  sender.setMaxMB(1);
  sender.setMB(MB0, TX, EXT);
  sender.mailboxStatus();

  // tp.begin();
  // tp.setWriteBus(&sender);
}

void loop() {
  delay(500);

  // Serial.println(digitalRead(BUTTON));
  digitalWrite(POWER, HIGH);


  if(digitalRead(BUTTON)){

    CAN_message_t msg;
    msg.id = ID;
    msg.len = 1;
    msg.buf[0] = 1;

    // Serial.println("Sent!");

    Serial.println(sender.write(msg));
    sender.mailboxStatus();

    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }

}