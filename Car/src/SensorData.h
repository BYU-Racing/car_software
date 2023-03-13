#ifndef SENSORDATA_H
#define SENSORDATA_H

enum sensorIDs { INERTIA_SWITCH, KEY_SWITCH, ACCEL_PEDAL, BRAKE_PEDAL };

class SensorData {
    public:
        
        enum sensorIDs sensorid;
        double data; //not sure about this data type
        double timestamp;
};



#endif