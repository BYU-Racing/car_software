#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>

class SensorData {
private:
    // Instantiate attributes
    int id;
    int priority;
    int* data;
    int timeStamp;

public:
    SensorData();
    SensorData(int id, int priority, int* data, int timeStamp);
    SensorData(int canMessage);

    int getTimeStamp() const;
    int getId() const;
    int getPriority() const;
    int* getData() const;

    void setId(int id);
    void setPriority(int priority);
    void setData(int* data);

    std::string formatCAN() const;
};

#endif // SENSORDATA_H