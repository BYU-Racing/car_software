#ifndef SWITCHSENSOR_H
#define SWITCHSENSOR_H

#include "Sensor.h"
#include "SensorData.h"
#include <Arduino.h>

class SwitchSensor : public Sensor {
    private:

        int SwitchVal = 0;
        float runner = 0;
        float ticker = 0;

        float comparitor = 0;
        bool isCritical;

    public:

        SwitchSensor(int id, int time, int pin, bool inCritical);


        int readInputs() override;
        bool readyToCheck();
        bool getCritical() override;

            // Additional methods for DigitalSensor
        int getPins();
        int getWaitTime();
        int getDataLength();
        int getId();

        int rescale(int data);
        int* buildData(int value);
        int* buildError();
        bool plugTest() override;


};

#endif