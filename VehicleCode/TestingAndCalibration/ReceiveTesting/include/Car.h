#ifndef CAR_H
#define CAR_H

#include "SensorData.h"  // Include the header for the SensorData class
#include <string>        // Include the header for string handling
#include <SD.h> 

class Car {
private:
    bool active;              // Indicates if the car is active
    bool key;                 // Indicates if the car has a key
    bool pushToStart;         // Indicates if the car uses push-to-start
    std::string fileName;     // File name for logging data
    int throttlePosition;     // Throttle position
    int timeZero;             // Starting time
    File dataFile;            // File for logging data
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
    CAN_message_t rmsg;
    int prevButtonState = 0;
    const int rescale = 100;
    const int startThreshold = 10;
    const int byteValue = 256;

public:
    // Constructor
    Car();
    Car(const std::string& logFileName);
    Car(const std::string& logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);

    // Destructor
    ~Car();

    // Method to shut down the car
    void shutdown();

    // Getters
    bool checkActive();

    // Setters
    void updateState();
    void buttonPushed();
    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);

    // Method to read sensors
    void readSensors();
    void checkKey();
    void checkButton();

    // Method to log sensor data
    void startSD(const std::string& logFileName);
    void logData(const SensorData& data);
    int deconstructSpeed(int* &data);

};

#endif // CAR_H