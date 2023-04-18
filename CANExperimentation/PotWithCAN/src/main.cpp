#include <Arduino.h>
#include <FlexCAN_T4.h>

#define POT A0
const float BIAS = 200;
const float RANGE = 800 - BIAS;

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

int speedCalc(int);

void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can1.begin();
  can1.setBaudRate(250000);
}

void loop() {
  

  CAN_message_t msg;
  msg.len=1;
  msg.id=1;
  msg.buf[0]=speedCalc(analogRead(POT));
  msg.id=2;
  can1.write(msg);

}

int speedCalc(int pot){
  if(pot < BIAS) return 0;

  float percent = (pot - BIAS) / RANGE;

  float speed = percent * 109 + 145;

  if(speed > 254) return 254;
  else return (int)speed;

}