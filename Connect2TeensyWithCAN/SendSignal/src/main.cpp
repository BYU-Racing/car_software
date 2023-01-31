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
#define LED 3
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> sender;
isotp<RX_BANKS_16, 512> tp;


void setup() {
  //Setup Serial Monitor
  Serial.begin(95238);

  //SETUP BUTTON PIN
  pinMode(BUTTON, INPUT);

  //SETUP LED PIN
  pinMode(LED, OUTPUT);

  //SETUP CANBUS PINS
  sender.begin();
  sender.setClock(CLK_60MHz);
  sender.setBaudRate(95238);
  sender.setMaxMB(16);

  tp.begin();
  tp.setWriteBus(&sender);
}

void loop() {

  delay(500);
  Serial.println(digitalRead(BUTTON));
  digitalWrite(LED, HIGH);

  uint8_t msg[1];

  if(digitalRead(BUTTON)){
    msg[0] = 1;
  }else{
    msg[0] = 0;
  }

  ISOTP_data config;
  config.id = 0x666;
  config.flags.extended = 0; /* standard frame */
  config.separation_time = 10; /* time between back-to-back frames in millisec */

  tp.write(config, msg, sizeof(msg));

}