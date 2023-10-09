#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include "Sensor.h"
#include "SensorData.h"

class DataCollector {
private:
    // sensor objects, starting time, and number of sensors
    Sensor** sensors;
    int timeZero;
    int numSensors;
    
    // Method to send signals to sensors
    void sendSignals();

    // Method to create SensorData
    SensorData createSensorData();

public:
    // Constructor
    DataCollector(Sensor** sensors, int numSensors, int startTime);

    // Destructor
    ~DataCollector();

    // Method to check sensor data
    void checkSensors();
};

#endif // DATACOLLECTOR_H
