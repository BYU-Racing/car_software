#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SensorData.h"

#define POT A0
const float BIAS = 200;
const float RANGE = 800 - BIAS;
const int rescale = 100;
const int startThreshold = 10;
const int byteValue = 256;

CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);
}

void loop() {
  
  if (can2.read(rmsg)) {
    SensorData msg = SensorData(rmsg);
    int* data = msg.getData();
    Serial.print("ID: ");
    Serial.println(rmsg.id, HEX);
    Serial.print("TORQUE: ");
    Serial.println(data[1] * byteValue + data[0]);
    Serial.print("SPEED: ");
    
    // Calculate speed and set it to zero if less than 10
    int speed = int(data[3] * byteValue + data[2]) / rescale;
    if (speed < startThreshold) {
        speed = 0;
    }   
    Serial.println(speed);
    Serial.println("");
  }
  else {
    Serial.println("error");
    delay(10);
  }
  delay(1000);
}