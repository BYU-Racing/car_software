#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>

class SensorData {
private:
    int id;
    int priority;
    double data;
    int timeStamp;

public:
    SensorData();
    SensorData(int id, int priority, double data, int timeStamp);
    SensorData(int canMessage);

    int getTimeStamp() const;
    int getId() const;
    int getPriority() const;
    double getData() const;

    void setId(int id);
    void setPriority(int priority);
    void setData(double data);

    std::string formatCAN() const;
};

#endif // SENSORDATA_H