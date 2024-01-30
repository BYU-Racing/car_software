#ifndef CAR_H
#define CAR_H

#include "SensorData.h"  // Include the header for the SensorData class
#include <string>        // Include the header for string handling

class Car {
private:
    bool active;              // Indicates if the car is active
    bool key;                 // Indicates if the car has a key
    bool pushToStart;         // Indicates if the car uses push-to-start
    std::string fileName;     // File name for logging data
    int throttlePosition;     // Throttle position
    int timeZero;             // Starting time

public:
    // Constructor
    Car(const std::string& logFileName);

    // Destructor
    ~Car();

    // Method to log sensor data
    void logData(const SensorData& data);

    // Method to update the state of the car
    void updateState();

    // Method to shut down the car
    void shutdown();

    // Method to check if the car is active
    bool checkActive();

    // Method to read sensors
    void readSensors();
};

#endif // CAR_H
