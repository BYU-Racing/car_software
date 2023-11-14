/*!
 * @brief Read and collect data from sensors to send to the dashboard and car
 * 
 * Whenever checkSensors gets called, this class reads data from every sensor 
 * that is ready to send data. It then creates a SensorData object for each 
 * piece of data and sends it to the dashboard and car over CAN.
 * 
 * @param sensors (Sensor**) An array of pointers to Sensor objects
 * @param numSensors (int) The number of sensors in the array
 * @param startTime (unsigned long) The time that the program started in milliseconds
 * @return None 
 */

#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include "Sensor.h"
#include "SensorData.h"

class DataCollector {
private:
    // sensor objects, starting time, and number of sensors
    Sensor** sensors;
    unsigned long timeZero;
    int numSensors;
    
    // Read signals from sensors
    void readData(Sensor* sensor);

    // Send a signal to Car and Dashboard objects
    void sendSignal(SensorData* sensorData);

public:
    // Constructor
    DataCollector(Sensor** sensors, int numSensors, unsigned long startTime);

    // Check sensor data and send signals
    void checkSensors();
};

#endif // DATACOLLECTOR_H
