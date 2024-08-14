#ifndef THROTTLE_H
#define THROTTLE_H

class Throttle {
    private:
        int throttle1 = 0;
        int throttle2 = 0;

        int torque = 0;
        int rollingTorque = 0;

        int countMisMatch = 0;

        bool throttleError;
        bool throttleActive;

        bool throttle1UPDATE;
        bool throttle2UPDATE;

        int readIn = 0;
        int magiMemory[4];

    public:
        Throttle();

        bool checkError();

        int calculateTorque();


        int getTorque();
        
        bool getStatus();

        bool getError();

        void setThrottle1(int* input);
        void setThrottle2(int* input);

        int consultMAGI(int input);

        bool getActive();
};

#endif