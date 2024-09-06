#ifndef BRAKE_H
#define BRAKE_H

class Brake {
    private:
        int brakeVal;
        int timeErrorStart;
        bool brakeActive;

        int errorState; //0 = no error, 1 = error, 2 = Critical Error

        int brakePin;

    public:
        Brake();
        Brake(int pin);

        void updateValue(int* data);

        bool checkError();


        bool getBrakeActive();
        int getBrakeVal();
        int getBrakeErrorState();

};

#endif