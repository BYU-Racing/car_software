/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Send a Signal over CAN when a button is pressed
 */

#include <Arduino.h>
#include <FlexCAN.h>

#define BUTTON 2
//TODO: DEFINE CANBUS PINS

void setup() {
  //SETUP BUTTON PIN
  pinMode(BUTTON, INPUT);

  //TODO: SETUP CANBUS PINS

}

void loop() {
  if(digitalRead(BUTTON)){
    //TODO: SEND SIGNAL OVER CAN
  }
}