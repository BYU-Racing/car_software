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
    
    // CHECK new function
    // Read signals from sensors
    void readData(Sensor* sensor);

    // CHECK add sensor parameter
    // Send a signal to Car and Dashboard objects
    void sendSignal(SensorData* sensorData);

    // CHECK remove this method
    // SensorData createSensorData(int raw_data, int sensorID, int priority);

public:
    // CHECK change startTime to unsigned long
    // Constructor
    DataCollector(Sensor** sensors, int numSensors, unsigned long startTime);

    // CHECK remove destructor
    // Destructor
    // ~DataCollector();

    // Check sensor data and send signals
    void checkSensors();
};

#endif // DATACOLLECTOR_H
