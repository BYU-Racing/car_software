/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Receive a Signal over CAN and turn on an LED
 */
#include <Arduino.h>
#include <FlexCAN.h>

#define LED 2
//TODO: DEFINE CANBUS PINS

void setup() {
  //SETUP LED PIN
  pinMode(LED, OUTPUT);

  //TODO: SETUP CANBUS PINS

}

void loop() {
  if(0){ //TODO: MAKE THIS IF STATEMENT DEPEND ON SIGNALS COMING FROM THE CANBUS
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }
}