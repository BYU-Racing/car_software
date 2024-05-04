#ifndef CAR_H
#define CAR_H

#include "SensorData.h"
#include <string>
#include <SD.h> 

// teensy hardware info
#define GO_PIN 23
#define ACCELERATOR_POT_1 3

// commands and logging integers
#define ID_ERROR 0
#define SHUTDOWN 1
#define CAR_ON 0
#define NO_COMMAND 2
#define COMMAND_IDX 1
#define START_STOP_ID 22

// global unchanging magic numbers
#define SCALE 100
#define START_THRESHOLD 10
#define BYTE_VALUE 256
#define MAX_NAME_LENGTH 6
#define MOTOR_SIGNAL_DELAY 1500



class Car {
private:
    // Car states
    bool goFast = false;                // Indicates if the motor should spin
    bool prevGoState = false;           // Previous state of the go switch
    unsigned long lastGoUpdate;         // Time of the last update
    unsigned long goUpdateSpeed = 500;  // Speed of the go switch update

    bool logState = false;              // Indicates if the car is logging data
    bool prevLogState = false;          // Previous state of the log switch
    unsigned long lastLogUpdate;        // Time of the last update
    unsigned long logUpdateSpeed = 500; // Speed of the log switch update
    unsigned long lastOffSignal;
    unsigned long repeatOffDelay = 500;// Delay for repeating the off command
    
    // Logging attributes
    int timeZero;                       // Starting time
    unsigned long saveDelay = 20000;    // Delay for saving data
    unsigned long lastSave;             // Time of the last save
    String fileName;                    // File name for logging data
    File dataFile;                      // File for logging data
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;

    // Global variables
    int speed;
    int count = 0;
    int i = 0;
    int j = 0;
    int* sensorData;
    int fileCount = 0;
    CAN_message_t rmsg;
    CAN_message_t startMotor; 
    CAN_message_t stopMotor;

    // Helper methods for logging data and SD card
    void logData(SensorData*);
    void saveSD();
    void startSD();
    void writeHeader();
    void shutdown();

    // Hardware checking
    void updateState(bool newState);
    void checkToLog();
    void countFiles();

    // Helper methods for setting up the SD card
    String updateFileName();
    int getMaxNumber();
    void writeNumber(const int&);
    String assembleName(const int&);
    int tempLength(const int&);

public:
    // Constructors and Destructors
    Car();
    Car(String logFileName, FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan);
    ~Car();
    void initialize(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>, int);

    // Setters
    void refreshLog();
    void setSaveDelay(int);
    void setLogState(bool);
    void resetTimeZero(unsigned long);
    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan);

    void sendMotorSignal(int, int, int);
    int deconstructSpeed(int*); // not used rn

    // Method to save data
    void createNewCSV();
    void readSensors();
};

#endif // CAR_H