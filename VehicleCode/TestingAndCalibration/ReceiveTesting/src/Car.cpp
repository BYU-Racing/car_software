#include "Car.h"
#include <SD.h> 

#define KEY_PIN 24
#define BUTTON_PIN 25
#define ACCELERATOR_POT_1 3
#define ID_ERROR 0
#define SHUTDOWN 1
#define NO_SHUTDOWN 0
#define COMMAND_IDX 1

Car::Car(){
    active = false;
    key = false;
    pushToStart = false;
    throttlePosition = 0;
    timeZero = millis();
}

void Car::startSD(const std::string& logFileName){
    fileName = logFileName;
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);

    // Initialize SD card
    if (!SD.begin(10)) {  // Use the appropriate pin for your SD module
        Serial.println("SD initialization failed!");
    }
    Serial.println("SD initialization done.");
}

// Constructor
Car::Car(const std::string& logFileName) {
    active = false;
    key = false;
    pushToStart = false;
    fileName = logFileName;
    throttlePosition = 0;
    timeZero = millis();
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);

    // Initialize SD card
    if (!SD.begin(10)) {  // Use the appropriate pin for your SD module
        Serial.println("SD initialization failed!");
    }
    Serial.println("SD initialization done.");
}

Car::Car(const std::string& logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2) {
    active = false;
    key = false;
    pushToStart = false;
    fileName = logFileName;
    throttlePosition = 0;
    timeZero = millis();
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    this->can2 = can2;

    // Initialize SD card
    if (!SD.begin(10)) {  // Use the appropriate pin for your SD module
        Serial.println("SD initialization failed!");
        return;
    }
    Serial.println("SD initialization done.");
}

// Destructor
Car::~Car() {
    shutdown();
}

// Method to log sensor data
void Car::logData(const SensorData& data) {
    if (dataFile) {
        // Write data to the file in CSV format
        dataFile.print(data.getId());
        dataFile.print(",");
        dataFile.print(data.getTimeStamp());
        dataFile.print(",");

        int* sensorData = data.getData();
        for (int i = 0; i < data.length(); i++) {
            dataFile.print(sensorData[i]);
            if (i < data.length() - 1) {
                dataFile.print(",");
            }
        }
        dataFile.println();

    } else {
        Serial.println("Error opening file");
    }
}

// Car is active if key is turned and button is pushed
void Car::updateState() {
    // Implement state update logic here
    active = key && pushToStart;
}

// Method to push the button
void Car::buttonPushed() {
    pushToStart = !pushToStart;
    updateState();
}

// Method to check if the key is turned
void Car::checkKey() {
    key = digitalRead(KEY_PIN);
    updateState();
}

// Method to check if the button is pushed
void Car::checkButton() {
    int buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != prevButtonState) {
        if (buttonState == HIGH) {
            buttonPushed();
        }
        prevButtonState = buttonState;
    }
}

/**
 * @brief Set the CAN bus
 * @param can2 (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
void Car::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2) {
    this->can2 = can2;
}

// Method to shut down the car
void Car::shutdown() {
    // Update the state
    key = false;
    pushToStart = false;
    active = false;

    // Close the file
    if (dataFile) {
        dataFile.close();
    }
}

// Method to check if the car is active
// CHECK: not used rn
bool Car::checkActive() {
    return active;
}

// Method to read sensors
void Car::readSensors() {
    if (active && can2.read(rmsg)) {
        SensorData msg = SensorData(rmsg);

        // update the motor controller
        if (msg.getId() == ACCELERATOR_POT_1) {
            can2.write(msg.formatCAN());
        }

        // log the data
        logData(msg);

        if (msg.getId() == ID_ERROR and msg.getData()[COMMAND_IDX] == SHUTDOWN) {
            shutdown();
        }
    }
}

// Method to deconstruct data
int Car::deconstructSpeed(int* &data) {
    int speed = int(data[3] * byteValue + data[2]) / rescale;
    if (speed < startThreshold) {
        speed = 0;
    }
    return speed;
}