#include "Car.h"
#include <SD.h> 

#define KEY_PIN 24
#define BUTTON_PIN 25 // not used rn
#define SWITCH_PIN 25
#define LOG_PIN 26
#define ACCELERATOR_POT_1 3
#define ID_ERROR 0
#define SHUTDOWN 1
#define NO_SHUTDOWN 0
#define COMMAND_IDX 1


/**
 * @brief Default constructor for Car class
*/
Car::Car(){
    active = false;
    key = false;
    switchOn = false;
    throttlePosition = 0;
    timeZero = millis();
    buttonState = 0;
    speed = 0;
}

/**
 * @brief Fancy constructor for Car class
 * 
 * @param logFileName (const char*) The name of the log file
 * @param can2 (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
Car::Car(String logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2) {
    active = false;
    key = false;
    switchOn = false;
    fileName = logFileName;
    throttlePosition = 0;
    timeZero = millis();
    can2 = can2;
}

/**
 * @brief Destructor for Car class
*/
Car::~Car() {
    shutdown();
}


/**
 * @brief Method to start the SD card
 * 
 * @param logFileName (const char*) The name of the log file
*/
void Car::startSD(){
    // get fileName and check for errors
    // fileName = updateFileName().c_str();
    fileName = updateFileName();
    if (strlen(fileName.c_str()) == 0) {
        fileName = "data.csv";
        Serial.println("Error: Latest file number not found.");
    }

    // Write the header
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    if (dataFile) {
        dataFile.println("ID, Time, Data");
    } else {
        Serial.println("Error: Can't open/start file.");
        delay(10000);
    }
    dataFile.close();
}



// -------------------------- HELPER FUNCTIONS -------------------------------------------


/**
 * @brief Method to log sensor data
 * 
 * @param data (const SensorData&) The sensor data to be logged
*/
void Car::logData(const SensorData& data) {
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    if (dataFile) {
        if (active && logState) {
            // Write data to the file in CSV format
            dataFile.print(data.getId());
            dataFile.print(",");
            dataFile.print(data.getTimeStamp());
            dataFile.print(",");

            sensorData = data.getData();
            for (int i = 0; i < data.length(); i++) {
                dataFile.print(sensorData[i]);
                if (i < data.length() - 1) {
                    dataFile.print(",");
                }
            }
            dataFile.println();
        } else {
            Serial.println("Waiting for permission to start logging.");
        }
    } else {
        Serial.println("Error: File not open.");
    }
    dataFile.close();
}


// Method to read sensors
void Car::readSensors() {
    // update states
    checkKey();
    checkSwitch();
    checkToLog();

    // read CAN
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
    speed = int(data[3] * byteValue + data[2]) / rescale;
    if (speed < startThreshold) {
        speed = 0;
    }
    return speed;
}

String Car::updateFileName() {
    // Initialize SD card
    if (!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("SD initialization failed!");
    }
    Serial.println("SD initialization done.");
    
    // Open the SD card directory
    File nameFile = SD.open("/fileNames.txt");
    if (!nameFile) {
        Serial.println("Failed to open root directory!");
    }
    String line;
    int maxNumber = 000000;
    while (nameFile.available()) {
        line = nameFile.readStringUntil('\n');
        int fileNumber = line.toInt();
        if(fileNumber > maxNumber) {
            maxNumber = fileNumber;
        }
    }
    nameFile.close();

    // Increment the max file number by one
    maxNumber++;
    nameFile = SD.open("/fileNames.txt", FILE_WRITE);
    nameFile.println(maxNumber);
    nameFile.close();

    // Convert the incremented file number to a string padded with zeros
    String incrementedFileName = String(maxNumber) + ".csv"; // Assuming maximum 6 digits
    return incrementedFileName;
}



// -------------------------- GETTERS AND SETTERS -------------------------------------------


/**
 * @brief Set the CAN bus
 * @param can2 (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
void Car::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2) {
    can2 = can2;
}

// Method to shut down the car
void Car::shutdown() {
    // Update the state
    key = false;
    switchOn = false;
    active = false;
    logState = false;

    // Close the file
    if (dataFile) {
        dataFile.close();
    }
}


// Car is active if key is turned and button is pushed
void Car::updateState() {
    // Implement state update logic here
    active = key && switchOn;
}

// Method to check if the key is turned
void Car::checkKey() {
    key = digitalRead(KEY_PIN);
    updateState();
}

void Car::checkSwitch() {
    switchOn = digitalRead(SWITCH_PIN);
    updateState();
}

void Car::checkToLog() {
    logState = digitalRead(LOG_PIN);
}

// Method to check if the car is active
// not used rn
bool Car::checkActive() {
    return active;
}


// Method to push the button
// Not used rn
void Car::buttonPushed() {
    switchOn = !switchOn;
    updateState();
}

// Method to check if the button is pushed
// Not used rn
void Car::checkButton() {
    buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != prevButtonState) {
        if (buttonState == HIGH) {
            buttonPushed();
        }
        prevButtonState = buttonState;
    }
}