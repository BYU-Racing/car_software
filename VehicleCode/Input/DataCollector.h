#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include "Sensor.h"
#include "SensorData.h"

class DataCollector {
private:
    Sensor* sensors;   // Array of Sensor objects
    int timeZero;      // Starting time
    int numSensors;   // Number of sensors

public:
    // Constructor
    DataCollector(int numSensors, int startTime);

    // Destructor
    ~DataCollector();

    // Method to send signals to sensors
    void sendSignals();

    // Method to check sensor data
    void checkSensors();

    // Method to create SensorData
    SensorData createSensorData();
};

#endif // DATACOLLECTOR_H
