#include <SPI.h>
#include <SD.h>


void setup() {
  Serial.begin(9600); // Initialize serial communication
  while (!Serial) {
    ; // Wait for serial monitor to open
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
}

void loop() {
  File dataFile = SD.open("test_load.csv");

  if (dataFile) {
    Serial.println("test_load.csv:");

    // read from the file and send over serial port:
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    // close the file:
    dataFile.close();
  } else {
    Serial.println("Error opening test_load.csv");
  }

  delay(1000);
}