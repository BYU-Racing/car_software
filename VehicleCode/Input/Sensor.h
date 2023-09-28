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
    // Instantiate attributes
    int* inputPins;
    int readFrequency;
    int previousUpdateTime;
    enum SensorID sensorID;
    int priority;

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
