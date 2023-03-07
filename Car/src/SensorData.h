#ifndef SENSORDATA_H
#define SENSORDATA_H

class SensorData {
    private:
        bool keyPosition;
        bool inertiaShutdown;

    public:
        bool getKeyPosition() {return keyPosition; }
        void setKeyPosition(bool val) { keyPosition = val;}
        bool getInertiaShutdown() { return inertiaShutdown; }
        void setInertiaShutdown(bool val) { inertiaShutdown = val; }

};



#endif