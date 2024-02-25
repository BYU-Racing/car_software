#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SensorData.h"
#include "Car.h"

#define POT A0
const int byteValue = 256;
unsigned long startTime = 0;

CAN_message_t rmsg1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
Car car;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  car.startSD();

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);
  car.setCAN(can2);
  startTime = millis();
}

void loop() {
  car.readSensors();

  // TESTING Car w/o CAN -------------------------------------------
  // make a basic sensor data pointer
  if (millis() - startTime > 5000) {
    car.shutdown();
    Serial.println("Shutting down after 5 seconds of operation.");
    while(1);
  }
  int* fake_data = new int[4];
  fake_data[0] = 0;
  fake_data[1] = 1;
  fake_data[2] = 2;
  fake_data[3] = 3;
  SensorData dataObj = SensorData(0, fake_data, 4, millis());
  dataObj.toString();
  Serial.println("");
  car.logData(dataObj);
  // END TESTING  Car w/o CAN ---------------------------------------
  
  if (can2.read(rmsg1)) {
    SensorData msg1 = SensorData(rmsg1);
    if (msg1.getId() == 0) {
      Serial.println("Error message received");
    }
    else {
      int* data = msg1.getData();
      Serial.print("ID: ");
      Serial.println(rmsg1.id, HEX);
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
    // Serial.println("error");
    delay(500);
  }
  // delay(1000);
}



// // Include HX711 library and wire library (the latter for SD card module)
// #include <Wire.h>

// // Include libraries for SD card module
// #include <SPI.h>
// #include <SD.h>

// // Define pins
// #define LOAD_DT 2 // Wire to DT
// #define LOAD_SCK 3 // Wire to SCK
// #define BUTTON 7 // Wire to button

// // Define variables for load cell reading & calibration factor
// double reading; // load cell value
// double A; // variable to track time
// float calibration_factor = -504000;

// // Objects for scale and card module
// File myFile;

// // Initial loop (run once)
// void setup() {
  
//   // Open serial communications and wait for port to open
//   Serial.begin(9600);
//   while (!Serial) {
//     ; // wait for serial port to connect. Needed for native USB port only
//   }

//   // Initialize communication with microSD card
//   Serial.print("Initializing SD card...");
//   if (!SD.begin(BUILTIN_SDCARD)) {
//     Serial.println("initialization failed!");
//     while (1);
//   }
//   Serial.println("initialization done.");


//   // Apply calibration factor to scale and print to serial monitor
//   Serial.print("Calibration factor: ");
//   Serial.println(calibration_factor);

//   // Set up digital pin connected to button
//   pinMode(BUTTON, INPUT);
// }

// void loop() {

//   // Check for button depress. If depressed, record data.

//     // Set reference time
//     A = micros()/1e6;
    
//     // Open file on microSD card
//     myFile = SD.open("test.txt", FILE_WRITE);
//     Serial.println(" Writing to test.txt...");

//     // Print column headers
//     myFile.println("Time(s) Force(mN)"); // mN = milliNewton
  
//     // Write data to file. If the file exists, the data will be
//     // appended to the end of the file.
//     for (int i = 0; i < 100; i++) {
//       myFile.print(micros()/1e6 - A, 8);
//       myFile.print(" ");
//       // Multiply reading by 9.807 to convert to force (F = mg)
//       myFile.println(-reading*1000*9.807, 5);
//     }

//     // Print blank line after last data point to make it easier
//     // to find where new data sets begin
//     myFile.println(" ");
   
//     // Close the file:
//     myFile.close();
//     Serial.println("Done.");
//     delay(2000);
//   }
