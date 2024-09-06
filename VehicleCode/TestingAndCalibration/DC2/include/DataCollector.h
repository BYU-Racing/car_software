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
    // Attributes: sensor objects, starting time, and number of sensors
    Sensor** sensors;
    unsigned long timeZero;
    int numSensors;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

    // Global variables
    int sendID = 0;
    int sendLength = 0;
    int i = 0;
    int rawData = 0;
    int* sendData;
    int health;

    CAN_message_t msg;


    
    // Read signals from sensors
    void readData(Sensor* sensor);

    // Send a signal to Car and Dashboard objects
    void sendSignal(SensorData* sensorData);

    // Send the start log command to the Car Object
    void sendLog(bool driveState);

    void runHealth();

    void sendHealthReport();

public:
    // Constructor
    DataCollector(Sensor** sensors, int numSensors, unsigned long startTime);

    // Check sensor data and send signals
    void checkSensors();

    // Getters and Setters
    void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2);
    void resetTimeZero(unsigned long startTime);
};

#endif // DATACOLLECTOR_H