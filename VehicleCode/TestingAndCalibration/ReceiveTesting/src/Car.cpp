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
    checkToLog();
    updateState();
    setLogState(true); // TODO remove after testing

    if (myCan.read(rmsg)) {
        SensorData* msg = new SensorData(rmsg);

        // log the data
        logData(msg);

        // save the data on the SD card
        saveSD();

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
    if (logState) {
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
    } else {
        Serial.print("Waiting: Log state=");
        Serial.println(logState);
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
        Serial.println("Saving to SD card.");
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
        dataFile.println("ID, Time, Data");
    } else {
        Serial.println("Error: Can't open/start file.");
        // Warning: infinite while loop if file can't be opened
        while(1);
    }
    // New approach leaves the file open and closes it every saveDelay milliseconds
    // dataFile.close();
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
    goFast = false;
    logState = false;

    // Close the file
    if (dataFile) {
        dataFile.close();
    }

    // TODO: update error LED
    sendMotorSignal(100, NO_COMMAND);
}

/**
 * @brief Reset the time zero
 * @param startTime (unsigned long) The time the car started
 */
void Car::resetTimeZero(unsigned long startTime) {
    timeZero = startTime;
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
void Car::updateState() {
    if (millis() - lastGoUpdate > goUpdateSpeed) {
        goFast = digitalRead(GO_PIN);
        lastGoUpdate = millis() + timeZero;
        sendMotorSignal(0, NO_COMMAND);
        prevGoState = goFast;
    }
}

/**
 * @brief Method to send a signal to the motor controller
 * 
 * @param duration (int) The number of times to send the signal
 * @param command (int) The command to send to the motor controller
 *    - NO_COMMAND: Send the signal based on the go switch
 *    - NO_SHUTDOWN: Send the signal to start the motor
 *    - SHUTDOWN: Send the signal to stop the motor
 * 
 * Sends a signal to the motor controller to turn on or off
 * based on the state of the go switch
*/
void Car::sendMotorSignal(int duration, int command) {
    for (i = 0; i < duration; i++) {

        // choose appropriate signal
        if (command == NO_SHUTDOWN || (goFast && !prevGoState)) {
            myCan.write(startMotor);
        }
        else if (command == SHUTDOWN || !goFast) {
            myCan.write(stopMotor);
        }

        // add a delay if sending multiple signals
        if (duration == 0) {
            break;
        }
        delay(MOTOR_SIGNAL_DELAY);
    }
}

/**
 * @brief Method to check the log switch and set the log state
 * 
 * Reads the log switch and sets the log state of the car
 * Updates the most last log update time
 * Opens or closes the file for logging data as necessary
*/
void Car::checkToLog() {
    if (millis() - lastLogUpdate > logUpdateSpeed) {
        logState = digitalRead(LOG_PIN);
        lastLogUpdate = millis() + timeZero;
        setLogState(logState);
        prevLogState = logState;
    }
}

/**
 * @brief Method to set the log state of the car

 * Opens or closes the file for logging data as necessary
*/
void Car::setLogState(bool state) {
    if (!logState && prevLogState && dataFile) {
        dataFile.close();
    } else if (logState && !prevLogState && !dataFile) {
        dataFile = SD.open(fileName.c_str(), FILE_WRITE);
    }
}
