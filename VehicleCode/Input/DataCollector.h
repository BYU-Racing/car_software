#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include "Sensor.h"
#include "SensorData.h"

class DataCollector {
private:
    // sensor objects, starting time, and number of sensors
    Sensor* sensors;
    int timeZero;
    int numSensors;

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
