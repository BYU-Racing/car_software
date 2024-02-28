/*
 * BYU RACING
 * Authors    David Reinhardt
 * Goal: Send signals on the CANBus to verify that
 *       the teensy and the wiring is correct
 */

#include <Arduino.h>
#include <FlexCAN_T4.h>

CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

bool state;

#define LED 13

unsigned long prev = 0;

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);

  pinMode(LED, OUTPUT);
  state = LOW;

  prev = millis();
}

void loop() {
  
  // flip the states value
  state = !state;

  if(can2.read(rmsg)) {
    if(rmsg.id == 2){
    Serial.println(rmsg.buf[0]);
    // write the value to the LED
    digitalWrite(LED, rmsg.buf[0]);
    
    Serial.print("Message ID:");
    Serial.println(rmsg.id, HEX );
    }
  }

  if (millis() - prev >= 500) {
    // CREATE AND SEND THE CAN MESSAGE
    prev = millis();
    CAN_message_t msg;
    msg.len=1;
    msg.buf[0]=state;
    msg.id=3;
    can2.write(msg);
    Serial.println("sent");
  }
}
