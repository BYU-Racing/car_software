#ifndef CAR_H
#define CAR_H

#include "SensorData.h"  // Include the header for the SensorData class
#include <string>        // Include the header for string handling
#include <SD.h> 


class Car {
private:
    // Car states
    bool active;              // Indicates if the car is active
    bool key;                 // Indicates if the car has been turned on with the key
    bool switchOn;            // Indicates if the car has been switched on
    bool logState;            // Indicates if the car is logging data
    int buttonState;          // State of the button (not used rn)

    // Other attributes
    String fileName;          // File name for logging data
    int throttlePosition;     // Throttle position
    int timeZero;             // Starting time
    File dataFile;            // File for logging data
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

    // Global variables
    int speed;
    int count = 0;
    int i = 0;
    int* sensorData;
    SensorData msg;
    CAN_message_t rmsg;
    int prevButtonState = 0;
    const int rescale = 100;
    const int startThreshold = 10;
    const int byteValue = 256;
    const int maxNameLength = 6;


public:
    // Constructors and Destructors
    Car();
    Car(String logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);
    ~Car();
    void shutdown();

    // Getters and setters
    bool checkActive();
    void updateState();
    void buttonPushed();
    void setActive(bool);
    void setLogState(bool);
    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);

    // Method to read sensors
    void readSensors();
    void checkKey();
    void checkButton();
    void checkSwitch();
    void checkToLog();

    // Method to log sensor data
    void createNewCSV();
    void writeHeader();
    void logData(const SensorData&);
    int deconstructSpeed(int*);
    String updateFileName();
    void startSD();
    int getMaxNumber();
    void writeNumber(const int&);
    String assembleName(const int&);
    int tempLength(const int&);
};

#endif // CAR_H
