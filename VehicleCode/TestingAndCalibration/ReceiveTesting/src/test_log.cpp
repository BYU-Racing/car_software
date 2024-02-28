// #include <Arduino.h>
// #include <FlexCAN_T4.h>
// #include "SensorData.h"
// #include "Car.h"

// #define POT A0
// const int byteValue = 256;
// unsigned long startTime = 0;

// CAN_message_t rmsg1;
// FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
// Car car;

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Start");
//   car.createNewCSV();

//   // SET UP CAN
//   can2.begin();
//   can2.setBaudRate(250000);
//   car.setCAN(can2);
//   startTime = millis();
// }

// void loop() {
//   car.readSensors();

//   // TESTING Car w/o CAN -------------------------------------------
//   // make a basic sensor data pointer
//   if (millis() - startTime > 5000) {
//     car.shutdown();
//     Serial.println("Shutting down after 5 seconds of operation.");
//     while(1);
//   }
//   int* fake_data = new int[4];
//   fake_data[0] = 0;
//   fake_data[1] = 1;
//   fake_data[2] = 2;
//   fake_data[3] = 3;
//   SensorData dataObj = SensorData(0, fake_data, 4, millis());
//   dataObj.toString();
//   Serial.println("");
//   car.logData(dataObj);
//   // END TESTING  Car w/o CAN ---------------------------------------
  
//   // if (can2.read(rmsg1)) {
//   //   SensorData msg1 = SensorData(rmsg1);
//   //   if (msg1.getId() == 0) {
//   //     Serial.println("Error message received");
//   //   }
//   //   else {
//   //     int* data = msg1.getData();
//   //     Serial.print("ID: ");
//   //     Serial.println(rmsg1.id, HEX);
//   //     Serial.print("TORQUE: ");
//   //     Serial.println(data[1] * byteValue + data[0]);
//   //     Serial.print("SPEED: ");
      
//   //     // Calculate speed and set it to zero if less than 10
//   //     int speed = car.deconstructSpeed(data);  
//   //     Serial.println(speed);
//   //     Serial.println("");
//   //   }
//   // }
//   // else {
//   //   // Serial.println("error");
//   //   delay(500);
//   // }
//   // delay(1000);
// }
