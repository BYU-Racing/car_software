#include "Car.h"
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SensorData.h"
#include <fstream>
    using std::ifstream, std::ostream;

/**
 * @brief Default constructor
 * 
 * @param logFileName (const std::string&) The name of the log file
*/
Car::Car(const std::string& logFileName) {
    this->active = false;
    this->key = false;
    this->pushToStart = false;
    this->fileName = logFileName;
    this->throttlePosition = 0;
    this->timeZero = millis();

    if (!isCSVFile(logFileName)) {
        this->dataFile = SD.open(logFileName, FILE_WRITE);
    }
    else {
        throw std::invalid_argument("Invalid file format. Expected a CSV file.");
    }
}


/**
 * @brief Destructor
*/
Car::~Car() {}

// TODO: implement this method
void Car::logData(const SensorData& data) {
    if (active) {
        // check if the file is open
        if (!dataFile.is_open()) {
            std::cerr << "Error opening file for writing." << std::endl;
            return;
        }

        // write the data to the file
        int id = data.getSensorID();
        // if (id == 0) {
            dataFile.print(id, data.getTimeStamp(), data.getData());
        // } else {
        //     dataFile.print(id, data.getTimeStamp(), data.getData());
        // }
    }
}


/**
 * @brief Update the state of the car
*/
void Car::updateState() {
    active = (key && pushToStart);
}

// TODO: implement this method
void Car::shutdown() {
    // send a signal to the motor control to turn off
    active = false;
    key = false;
    pushToStart = false;

    // close the log file
    dataFile.close();
}


// TODO: implement this method
void Car::updateMotor(CAN_message_t percent) {
    // send a signal to the motor control to update the motor
    if (active) {}
}

/**
 * @brief Check if the car is active
 * 
 * @return (bool) True if the car is active, false otherwise
*/
bool Car::checkActive() {
    return active;
}

/**
 * @brief Turn the key to start or stop the car
*/
void Car::turnKey() {
    key = !key;
}

/**
 * @brief Push to start or stop the car
*/
void Car::pushStart() {
    pushToStart = !pushToStart;
}

/**
 * @brief Check if a file is a CSV file
 * 
 * @param file_name (const std::string&) The name of the file
 * 
 * @return (bool) True if the file is a CSV file, false otherwise
*/
bool isCSVFile(const std::string& file_name) {
    // Check if the file_name ends with ".csv"
    return file_name.length() >= 4 && file_name.substr(file_name.length() - 4) == ".csv";
}