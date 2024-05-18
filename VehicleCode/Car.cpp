#include "Car.h"

/**
 * @brief Default constructor for Car class
*/
Car::Car() {
    goFast = false;
    logState = false;
    timeZero = millis();
    lastSave = millis();
    speed = 0;

    startMotor.len = 8;
    startMotor.buf[0] = 0;
    startMotor.buf[1] = 0;
    startMotor.buf[2] = 0;
    startMotor.buf[3] = 0;
    startMotor.buf[4] = 0;
    startMotor.buf[5] = 0;
    startMotor.buf[6] = 0;
    startMotor.buf[7] = 0;
    startMotor.id = 192; 

    stopMotor = startMotor;
    stopMotor.buf[4] = 1;
}


/**
 * @brief Fancy constructor for Car class
 * 
 * @param logFileName (const char*) The name of the log file
 * @param myCan (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
 * 
 * Calls the default constructor to initialize the rest of the attributes
*/
Car::Car(String logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan) : Car() {
    fileName = logFileName;
    this->myCan = myCan;
}


/**
 * @brief Destructor for Car class
*/
Car::~Car() {
    shutdown();
}


/**
 * @brief Initializes the Car object in one command
 * 
 * @param myCan (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus object
 * @param saveDelay (int) The delay interval for saving data
 * 
 * Creates a new CSV file for logging
 * Initializes the CAN bus object
 * Sets the save delay interval
 * Sets the logging state to true
 * Resets the time zero for logging purposes.
 */
void Car::initialize(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan, int saveDelay) {
    // createNewCSV();
    setCAN(myCan);
    setSaveDelay(saveDelay);
    // refreshLog();
    resetTimeZero(millis());
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

    if (myCan.read(rmsg)) {


        //Checks if it is a start stop message!
        if(rmsg.id == 222) {
            if(rmsg.buf[0] == 1) {
                updateState(true);
                //START HORN
                digitalWrite(HORN_PIN, HIGH);
                //3 SECOND HORN SOUND
                delay(3500);
                //STOP HORN
                digitalWrite(HORN_PIN, LOW);
            }
            else {
                updateState(false);
            }
            return;
        }

        SensorData* msg = new SensorData(rmsg);

        if (logState) {
            // log the data, save SD every few seconds
            logData(msg);
            saveSD();
        } else { 
            // Serial.println("Waiting: Log state is False");
        }

        // check for shutdown command
        if (msg->getId() == ID_ERROR && msg->getData()[COMMAND_IDX] == SHUTDOWN) {
            delete msg;
            shutdown();
        } else {
            delete msg;
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
void Car::logData(SensorData* data) {
    if (dataFile) {
        // Write data to the file in CSV format
        dataFile.print(data->getId());
        dataFile.print(",");
        dataFile.print(millis() - timeZero);
        dataFile.print(",");

        sensorData = data->getData();
        for (i = 0; i < data->length(); i++) {
            dataFile.print(sensorData[i]);
            if (i < data->length() - 1) {
                dataFile.print(",");
            }
        }
        dataFile.println();
    } else {
        Serial.println("Error: File not open.");
    }
}


/**
 * @brief Method to deconstruct the speed from the CAN message
 * See ThrottleSensorData.cpp for more details on the data format
 * 
 * @param data (int*&) The data from the CAN message 
*/
int Car::deconstructSpeed(int* data) {
    speed = int(data[3] * BYTE_VALUE + data[2]) / SCALE;

    // Set speed to zero if less than 10 (start threshold)
    if (speed < START_THRESHOLD) {
        speed = 0;
    }
    return speed;
}















// -------------------------- SD CARD FUNCTIONS -------------------------------------------


/**
 * @brief Method to save data to the SD card by closing then reopening the file
*/
void Car::saveSD() {
    if (millis() - lastSave > saveDelay) {
        lastSave = millis();
        if (dataFile) {
            dataFile.close();
        }
        dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    }
};


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
        Serial.println("Error: Latest file number not found. Saving to 'data.csv' instead.");
    }

    // create the file and write the header
    writeHeader();
}


/**
 * @brief Method to write the header of the CSV file
*/
void Car::writeHeader() {
    dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    if (dataFile) {
        dataFile.println("ID,Time,Data0,Data1,Data2,Data3,Data4,Data5,Data6,Data7");
    } else {
        Serial.println("Error: Can't open/start file.");
    }
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
 * Opens the fileNames.txt file and writes the new maximum file number
 * If the file does not exist, it is created
 * 
 * @param maxNumber (int) The new maximum file number
*/
void Car::writeNumber(const int &maxNumber) {
    File nameFile = SD.open("/fileNames.txt", FILE_WRITE);
    
    // Check if the file is open
    if (nameFile) {
        nameFile.println(maxNumber);
        nameFile.close();
    } else {
        Serial.println("Error: Unable to create or open fileNames.txt");
    }
}



/**
 * @brief Method to assemble the file name
 * Convert the incremented file number to a string padded with zeros
 * 
 * @param maxNumber (int) The maximum file number
 * 
 * @return (String) The assembled file name in the format "000000.csv"
*/
String Car::assembleName(const int &maxNumber) {
    String temp;
    for (int j = 0; j < tempLength(maxNumber); j++) {
        temp = "0" + temp;
    }
    return temp + String(maxNumber) + ".csv"; 
}


/**
 * @brief Method to determine the number of zeros to prepend to the file number
 * @param maxNumber (const int&) The maximum file number
 * @return (int) The number of zeros to prepend to the file number
*/
int Car::tempLength(const int &maxNumber) {
    count = 0;
    int temp = maxNumber; // definition is fine because function is only called once
    
    // Handle the cases for <=0 separately
    if (temp == 0) return 1;
    if (temp < 0) return 0;

    // Count the number of digits by repeatedly dividing by 10
    while (temp > 0) {
        temp /= 10;
        count++;
    }
    return MAX_NAME_LENGTH - count;
}










// -------------------------- GETTERS AND SETTERS -------------------------------------------


/**
 * @brief Set the CAN bus
 * @param myCan (FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>) The CAN bus
*/
void Car::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan) {
    this->myCan = myCan;
}

/**
 * @brief Method to shutdown the car
 * Sets all states to false and closes the SD card file
*/
void Car::shutdown() {
    // Update the state
    Serial.println("Shutting down the car.");
    goFast = false;
    logState = false;

    // Close the file
    if (dataFile) {
        dataFile.close();
    }
}

/**
 * @brief Reset the time zero
 * @param startTime (unsigned long) The time the car started
 */
void Car::resetTimeZero(unsigned long startTime) {
    timeZero = startTime;
    lastOffSignal = startTime;
}

/**
 * @brief Set the delay for saving data
*/
void Car::setSaveDelay(int delay) {
    if (delay >= 0) {
        saveDelay = delay;
    }
}

/**
 * @brief Set the log state of the car based on the log switch
 * 
 * Reads the log switch and sets the log state of the car
 * Updates the most last log update time
 * Sends a signal to the motor controller if necessary
*/
void Car::updateState(bool newState) {
    if (millis() - lastGoUpdate > goUpdateSpeed) {
        // update states
        goFast = newState;
        logState = goFast;
        lastGoUpdate = millis() + timeZero;
        lastLogUpdate = lastGoUpdate;

        // send a signal to the motor controller if the go switch changes
        if (goFast != prevGoState) {
            if (!goFast) {
                Serial.println("Closing file.");
                if (dataFile) {
                    dataFile.close();
                    Serial.println("Closed file.");
                }
            } else {
                createNewCSV();
            }
        } 
        prevGoState = goFast;
        prevLogState = logState;
    }
}



/**
 * @brief Method to set the log state of the car
 * @param state (bool) The new log state
*/
void Car::setLogState(bool state) {
    logState = state;
}


// NOT USED ANYMORE

/**
 * @brief NOT USED Method to check the log switch and set the log state
 * 
 * Reads the go switch and sets the log state of the car
 * Updates the most last log update time
 * Opens or closes the file for logging data as necessary
*/
void Car::checkToLog() {
    if (millis() - lastLogUpdate > logUpdateSpeed) {
        logState = digitalRead(GO_PIN);
        lastLogUpdate = millis() + timeZero;
        refreshLog();
        prevLogState = logState;
    }
}

/**
 * @brief NOT USED Method to set the log state of the car

 * Opens or closes the file for logging data as necessary
*/
void Car::refreshLog() {
    if (!logState && prevLogState && dataFile) {
        dataFile.close();
    } else if (logState && !prevLogState && !dataFile) {
        Serial.println("RefreshLog");
        Serial.println(fileName);
        dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    }
}


void Car::countFiles(){
    fileCount = 0;
    File root = SD.open("/");
    if (!root) {
        Serial.println("Failed to open directory.");
        return;
    }

    // Count files in the root directory
    while (true) {
        File entry = root.openNextFile();
        if (!entry) {
        break; // No more files
        }
        if (entry.isDirectory()) {
        continue; // Skip directories
        }
        fileCount++;
        entry.close();
    }

    // Close the root directory
    root.close();
}