#include "Error.h"
#include <FlexCAN_T4.h>
#include <Arduino.h>
#include "SensorData.h"


/**
 * @brief Default constructor for Error class
*/
Error::Error() {
    id = 0;
    data = {0};
    timeStamp = 0;
    dataLength = 0;
    sensorName = "";
    errorType = 0;
    errorMessage = "";
    shutDown = false;
}

/**
 * @brief Constructor for Error class
 * 
 * @param inId (int) The unique identifier for the sensor.
 * @param inData (int*) The data from the sensor.
 * @param inDataLength (int) The length of the data array.
 * @param inTimeStamp (unsigned long) The timestamp of the data.
 * @param inSensorName (std::string) The name of the sensor.
 * @param inErrorType (int) The type of error.
 *                          0: No Error
 *                          1: Warning
 *                          2: Critical
 *                          3: Fatal
 * @param inErrorMessage (std::string) The error message.
 * @param shutDown (bool) Whether or not the car should shut down.
*/
Error::Error(int inId, int* inData, int inDataLength, unsigned long inTimeStamp,
             std::string inSensorName, int inErrorType, std::string inErrorMessage, bool shutDown) {
    id = inId;
    data = inData;
    dataLength = inDataLength;
    timeStamp = inTimeStamp;
    sensorName = inSensorName;
    errorType = inErrorType;
    errorMessage = inErrorMessage;
    shutDown = shutDown;
}

/**
 * @brief CAN Constructor for Error class
 * 
 * @param canMessage (CAN_message_t) The CAN message to be converted to an Error.
 * Everything else is the same as the other constructor.
*/
Error::Error(CAN_message_t canMessage, std::string inSensorName, int inErrorType, std::string inErrorMessage, bool shutDown) {
    id = canMessage.id;
    timeStamp = canMessage.timestamp;
    dataLength = canMessage.len;
    data = new int[dataLength];
    for (int i = 0; i < dataLength; i++) {
        data[i] = canMessage.buf[i];
    }
    sensorName = inSensorName;
    errorType = inErrorType;
    errorMessage = inErrorMessage;
    shutDown = shutDown;
}


/**
 * @brief Destructor for Error class
*/
Error::~Error() {
    delete[] data;
}


// Getters and Setters

std::string Error::getSensorName() const {
    return sensorName;
}

int Error::getErrorType() const {
    return errorType;
}

std::string Error::getErrorMessage() const {
    return errorMessage;
}

void Error::setSensorName(std::string inSensorName) {
    sensorName = inSensorName;
}

void Error::setErrorType(int inErrorType) {
    errorType = inErrorType;
}

void Error::setErrorMessage(std::string inErrorMessage) {
    errorMessage = inErrorMessage;
}
