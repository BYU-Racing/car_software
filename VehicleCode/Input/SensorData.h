// TODO: Add class docstring

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>

class SensorData {
private:
    // Instantiate attributes
    int id;
    int priority;
    int* data;
    unsigned long timeStamp;

public:
    SensorData();
    SensorData(int id, int priority, int* data, unsigned long timeStamp);
    SensorData(CAN_Message_t canMessage);

    int getTimeStamp() const;
    int getId() const;
    int getPriority() const;
    int* getData() const;

    void setId(int id);
    void setPriority(int priority);
    void setData(int* data);
    void setTimeStamp(int timeStamp);

    std::string formatCAN() const;
};

#endif // SENSORDATA_H