#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SensorData.h"

// Note from the author Dallin
// I don't think we need this class. Instead we will send a SensorData object with a custom format.


class Error : public SensorData {
private:
    // Instantiate attributes
    std::string sensorName;
    int errorType;
    std::string errorMessage;
    bool shutDown;

public:
    // Constructor
    Error();
    Error(int id, int* data, int dataLength, unsigned long timeStamp,
          std::string sensorName, int errorType, std::string errorMessage, bool shutDown);
    Error(CAN_message_t canMessage, std::string sensorName, 
          int errorType, std::string errorMessage, bool shutDown);

    // Destructor
    ~Error();

    // Getters and Setters
    std::string getSensorName() const;
    int getErrorType() const;
    std::string getErrorMessage() const;

    void setSensorName(std::string sensorName);
    void setErrorType(int errorType);
    void setErrorMessage(std::string errorMessage);
};

#endif // ERROR_H