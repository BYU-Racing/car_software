#ifndef SENSOR_H
#define SENSOR_H

enum SensorID {
    SENSOR_ID_1,
    SENSOR_ID_2,
    SENSOR_ID_3,
    // Add more sensor IDs as needed
};

class Sensor {
protected:
    int* inputPins;           // Array of input pins
    int readFrequency;        // Read frequency in milliseconds
    int previousUpdateTime;   // Previous update time in milliseconds
    enum SensorID sensorID;   // Sensor ID
    int priority;             // Priority level

public:
    // Constructor
    Sensor(enum SensorID id, int freq, int prio);

    // Destructor
    virtual ~Sensor();  // Make the destructor virtual

    // Declare a pure virtual function
    virtual int* readInputs() = 0;

    // Method to check if it's ready to read
    virtual bool readyToCheck() = 0;
};

#endif // SENSOR_H
