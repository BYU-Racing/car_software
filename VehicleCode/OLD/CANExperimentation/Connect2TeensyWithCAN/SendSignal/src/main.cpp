/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Send a Signal over CAN when a button is pressed
 */

#include <Arduino.h>
#include <FlexCAN_T4.h>


const int ledPin = 3;

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> myCan1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan2;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> myCan3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
myCan1.begin();
myCan2.begin();
myCan3.begin();
myCan1.setBaudRate(9600);
myCan2.setBaudRate(9600);
myCan3.setBaudRate(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
CAN_message_t msg, rmsg;
msg.len=8;
msg.id=1;
msg.buf[0]=1;
msg.buf[1]=2;
msg.buf[2]=3;
msg.buf[3]=4;
msg.buf[4]=5;
msg.buf[5]=6;
msg.buf[6]=7;
msg.buf[7]=8;

myCan1.write(msg);
msg.id=2;
myCan2.write(msg);
msg.id=3;
myCan3.write(msg);

 if ( myCan1.read(rmsg) ) 
 {
 Serial.print("CAN1 "); 
 Serial.print("  ID: 0x"); Serial.print(rmsg.id, HEX );
 }
 if ( myCan2.read(rmsg) ) 
 {
 Serial.print("CAN2 "); 
 Serial.print("  ID: 0x"); Serial.print(rmsg.id, HEX );
 }
 Serial.println ("Hi!");

digitalWrite(ledPin, !digitalRead(ledPin));
delay (500);
}