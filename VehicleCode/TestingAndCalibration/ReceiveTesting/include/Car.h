#ifndef CAR_H
#define CAR_H

#include "SensorData.h"  // Include the header for the SensorData class
#include <string>        // Include the header for string handling
#include <SD.h> 

class Car {
private:
    bool active;              // Indicates if the car is active
    bool key;                 // Indicates if the car has been turned on with the key
    bool switchOn;            // Indicates if the car has been switched on
    bool logState;            // Indicates if the car is logging data
    String fileName;     // File name for logging data
    int throttlePosition;     // Throttle position
    int timeZero;             // Starting time
    File dataFile;            // File for logging data
    int buttonState;          // State of the button (not used rn)
    int speed;
    int* sensorData;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
    CAN_message_t rmsg;
    int prevButtonState = 0;
    const int rescale = 100;
    const int startThreshold = 10;
    const int byteValue = 256;

public:
    // Constructor
    Car();
    Car(String logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);

    // Destructor
    ~Car();
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
    void checkSwitch();
    void checkToLog();

    // Method to log sensor data
    void startSD();
    void logData(const SensorData& data);
    int deconstructSpeed(int* &data);
    String updateFileName();

};

#endif // CAR_H
