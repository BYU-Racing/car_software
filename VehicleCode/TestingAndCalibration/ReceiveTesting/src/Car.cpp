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
Car::Car() {
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




// -------------------------- DATA FUNCTIONS -------------------------------------------


/**
 * @brief Method to read sensors
 * 
 * Checks the key and switch to determine if the car is active
 * Reads the CAN bus for sensor data
 * Sends the throttle position to the motor controller
 * Logs the sensor data
 * Checks for a shutdown command in case of an error
*/
void Car::readSensors() {
    // update states
    checkKey();
    checkSwitch();
    checkToLog();
    setActive(true); // TODO remove after testing
    setLogState(true); // TODO remove after testing

    // read CAN
    Serial.print("Reading CAN: ");
    bool canRead = can2.read(rmsg);
    Serial.println(canRead);
    if (active && canRead) {
        msg = SensorData(rmsg);

        // update the motor controller
        if (msg.getId() == ACCELERATOR_POT_1) {
            throttlePosition = deconstructSpeed(msg.getData());
            can2.write(msg.formatCAN());
        }

        // log the data
        logData(msg);

        // check for shutdown command
        if (msg.getId() == ID_ERROR and msg.getData()[COMMAND_IDX] == SHUTDOWN) {
            shutdown();
        }
    }
}


/**
 * @brief Method to log sensor data
 * 
 * Opens the file and writes the sensor data in CSV format
 * Checks for errors in opening the file and the state of the car first
 * 
 * @param data (const SensorData&) The sensor data to be logged
*/
void Car::logData(const SensorData& data) {
    if (logState) { 
        dataFile = SD.open(fileName.c_str(), FILE_WRITE);
        if (dataFile) {
            // Write data to the file in CSV format
            dataFile.print(data.getId());
            dataFile.print(",");
            dataFile.print(data.getTimeStamp());
            dataFile.print(",");

            sensorData = data.getData();
            for (i = 0; i < data.length(); i++) {
                dataFile.print(sensorData[i]);
                if (i < data.length() - 1) {
                    dataFile.print(",");
                }
            }
            dataFile.println();
        } else {
            Serial.println("Error: File not open. ");
        }
        dataFile.close();
    } else {
        Serial.println("Waiting for permission to start logging.");
    }
}


/**
 * @brief Method to deconstruct the speed from the CAN message
 * See ThrottleSensorData.cpp for more details on the data format
 * 
 * @param data (int*&) The data from the CAN message 
*/
int Car::deconstructSpeed(int* data) {
    speed = int(data[3] * byteValue + data[2]) / rescale;

    // Set speed to zero if less than 10 (start threshold)
    if (speed < startThreshold) {
        speed = 0;
    }
    return speed;
}




// -------------------------- SD CARD FUNCTIONS -------------------------------------------


/**
 * @brief Method to start the SD card
 * 
 * Initializes the SD card and creates a new file for logging data
 * 
 * @param logFileName (const char*) The name of the log file
*/
void Car::createNewCSV() {
    // get fileName and check for errors
    fileName = updateFileName();
    Serial.println("File name: " + fileName);
    if (strlen(fileName.c_str()) == 0) {
        fileName = "data.csv";
        Serial.println("Error: Latest file number not found.");
    }

    writeHeader();
}


/**
 * @brief Method to write the header of the CSV file
*/
void Car::writeHeader() {
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    if (dataFile) {
        dataFile.println("ID, Time, Data");
    } else {
        Serial.println("Error: Can't open/start file.");
        delay(10000);
    }
    dataFile.close();
}



/**
 * @brief Method to update the file name
 * 
 * Reads from the fileNames.txt file to get the latest file number
 * Increments the latest file number by one and updates the fileNames.txt file
 * 
 * @return (String) The updated file name
*/
String Car::updateFileName() {
    startSD();
    int maxNumber = getMaxNumber() + 1;
    writeNumber(maxNumber);
    return assembleName(maxNumber);
}


/**
 * @brief Method to start the SD card
*/
void Car::startSD() {
    if (!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("SD initialization failed!");
    }
    Serial.println("SD initialization done.");
}


/**
 * @brief Method to get the maximum file number
*/
int Car::getMaxNumber() {
    // Open the SD card directory
    File nameFile = SD.open("/fileNames.txt");
    if (!nameFile) {
        Serial.println("Failed to open root directory!");
    }

    // Read the file and get the maximum number
    // Only runs once so don't worry about memory or global variables
    String line;
    int maxNumber = 0;
    while (nameFile.available()) {
        line = nameFile.readStringUntil('\n');
        int fileNumber = line.toInt();
        if (fileNumber > maxNumber) {
            maxNumber = fileNumber;
        }
    }

    // Close the file and return
    nameFile.close();
    return maxNumber;
}


/**
 * @brief Method to write the maximum file number to the fileNames.txt file
 * 
 * @param maxNumber (int) The new maximum file number
*/
void Car::writeNumber(int maxNumber) {
    File nameFile = SD.open("/fileNames.txt", FILE_WRITE);
    nameFile.println(maxNumber);
    nameFile.close();
}


/**
 * @brief Method to assemble the file name
 * Convert the incremented file number to a string padded with zeros
 * 
 * @param maxNumber (int) The maximum file number
 * 
 * @return (String) The assembled file name in the format "000000.csv"
*/
String Car::assembleName(int maxNumber) {
    String temp;
    for (int j = 0; j < tempLength(maxNumber); j++) {
        temp = "0" + temp;
    }
    return temp + String(maxNumber) + ".csv"; 
}


int Car::tempLength(int maxNumber) {
    return maxNameLength - 1 - (maxNumber / 10);
}




// -------------------------- GETTERS AND SETTERS -------------------------------------------


/**
 * @brief Set the CAN bus
 * @param can2 (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
void Car::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2) {
    this->can2 = can2;
}

/**
 * @brief Method to shutdown the car
 * 
 * Sets all states to false and closes the SD card file
*/
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

    // update error LED?
}

// Method to set the active state of the car for testing only
void Car::setActive(bool state) { 
    active = state;
}

// Method to set the log state of the car for testing only
void Car::setLogState(bool state) {
    logState = state;
}

// Car is active if key is turned and button is pushed
void Car::updateState() {
    active = key && switchOn;
}
// Method to check if the key is turned
void Car::checkKey() {
    key = digitalRead(KEY_PIN);
    updateState();
}
// Method to check if the power switch is flipped to the on position
void Car::checkSwitch() {
    switchOn = digitalRead(SWITCH_PIN);
    updateState();
}
// Method to check if the log switch is flipped to the on position
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
    buttonState = !buttonState;
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
