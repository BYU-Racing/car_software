#ifndef CAR_H
#define CAR_H

#include <SD.h>
#include <SPI.h>
#include <string>
#include "Input/SensorData.h"

class Car {
private:
    bool active;              
    bool key;
    int keyPin;
    bool pushToStart;
    std::string fileName;
    File file;
    int throttlePosition;
    int timeZero;
    const int chipSelect = BUILTIN_SDCARD; 

public:
    // Constructor
    Car(const std::string logFileName);

    // Destructor
    ~Car();

    // Method to log sensor data
    void logData(const SensorData data);

    // Method to update the state of the car
    void updateState();

    // Method to shut down the car
    void shutdown();

    // Method for emergency shutdown
    void emergencyShutdown();

    // Method to update the motor
    void updateMotor();

    // Method to check if the car is active
    bool checkActive();

    // Method to read sensors
    void readSensors();
};

#endif // CAR_H
