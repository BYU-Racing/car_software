#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SensorData.h"
#include "Car.h"

#define POT A0
const float BIAS = 200;
const float RANGE = 800 - BIAS;
const int rescale = 100;
const int startThreshold = 10;
const int byteValue = 256;

CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
Car car;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Start");
  car.startSD("data.csv");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);
  car.setCAN(can2);
}

void loop() {
  car.checkButton();
  car.checkKey();
  car.readSensors();

  // make a basic sensor data pointer
  int* data = new int[4];
  data[0] = 0;
  data[1] = 1;
  data[2] = 2;
  data[3] = 3;
  SensorData dataObj = SensorData(0, data, 1, millis());
  car.logData(dataObj);
  
  if (can2.read(rmsg)) {
    SensorData msg = SensorData(rmsg);
    if (msg.getId() == 0) {
      Serial.println("Error message received");
    }
    else {
      int* data = msg.getData();
      Serial.print("ID: ");
      Serial.println(rmsg.id, HEX);
      Serial.print("TORQUE: ");
      Serial.println(data[1] * byteValue + data[0]);
      Serial.print("SPEED: ");
      
      // Calculate speed and set it to zero if less than 10
      int speed = car.deconstructSpeed(data);  
      Serial.println(speed);
      Serial.println("");
    }
  }
  else {
    Serial.println("error");
    delay(500);
  }
  // delay(1000);
}