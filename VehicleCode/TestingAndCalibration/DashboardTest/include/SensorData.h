#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>
#include <Arduino.h>
#include <FlexCAN_T4.h>

class SensorData {
protected:
    // Instantiate attributes
    int id;
    int* data;
    unsigned long timeStamp;
    int dataLength;

public:
    // Constructor
    SensorData();
    // CHECK change timeStamp to unsigned long
    SensorData(int id, int* data, int dataLength, unsigned long timeStamp);
    // CHECK change canMessage to CAN_message_t
    SensorData(CAN_message_t canMessage);

    // CHECK add destructor
    // Destructor
    ~SensorData();

    int getTimeStamp() const;
    int getId() const;
    int getPriority() const;
    int* getData() const;
    int length() const;

    void setId(int id);
    void setData(int* data);
    // CHECK allow for setting timestamp
    void setTimeStamp(unsigned long timeStamp);

    // CHECK change output to CAN_message_t
    CAN_message_t formatCAN() const;
    void toString() const;
};

#endif // SENSORDATA_H