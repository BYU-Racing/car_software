#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>

class SensorData {
private:
    // Instantiate attributes
    int id;
    int priority;
    double data;
    int timeStamp;

public:
    // Constructor
    SensorData();
    // CHECK change data to double, timeStamp to unsigned long
    SensorData(int id, int priority, int data, unsigned long timeStamp);
    SensorData(int canMessage);

    // CHECK add destructor
    // Destructor
    ~SensorData();

    int getTimeStamp() const;
    int getId() const;
    int getPriority() const;
    double getData() const;

    void setId(int id);
    void setPriority(int priority);
    void setData(double data);
    // CHECK allow for setting timestamp
    void setTimeStamp(int timeStamp);

    // CHECK change output to CAN_message_t
    CAN_message_t formatCAN() const;
};

#endif // SENSORDATA_H