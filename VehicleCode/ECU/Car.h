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
    int timeZero;             // Starting time
    int saveDelay = 10000;    // Delay for saving data
    unsigned long lastSave;   // Time of the last save

    // Logging attributes
    String fileName;          // File name for logging data
    File dataFile;            // File for logging data
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

    // Other attributes
    int buttonState;          // State of the button (not used rn)
    int prevButtonState = 0;
    const int scale = 100;
    const int startThreshold = 10;
    const int byteValue = 256;
    const int maxNameLength = 6;

    // Global variables
    int speed;
    int count = 0;
    int i = 0;
    int* sensorData;
    CAN_message_t rmsg;

    // Helper methods for logging data and SD card
    void logData(SensorData*);
    void saveSD();
    void startSD();
    void writeHeader();
    void shutdown();

    // Hardware checking
    void updateState();
    void checkKey();
    void checkButton();
    void checkSwitch();
    void checkToLog();
    void buttonPushed();

    // Helper methods for setting up the SD card
    String updateFileName();
    int getMaxNumber();
    void writeNumber(const int&);
    String assembleName(const int&);
    int tempLength(const int&);

public:
    // Constructors and Destructors
    Car();
    Car(String logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);
    ~Car();

    // Setters
    void setActive(bool);
    void setLogState(bool);
    void setSaveDelay(int);
    void resetTimeZero(unsigned long);
    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);

    // Getters
    bool checkActive();
    int deconstructSpeed(int*); // not used rn

    // Method to save data
    void createNewCSV();
    void readSensors();
};

#endif // CAR_H
