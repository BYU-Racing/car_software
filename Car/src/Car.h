#ifndef CAR_H
#define CAR_H
//#include "IdleState.h"
//#include "State.h"

class Car {
    private:
        //State state;
        bool keyPosition;
        bool inertiaShutdown;

    public:
        Car() {}
        Car(int _ledPin) /*: state(IdleState(*this, _ledPin)) */{}
        void updateSensors(bool, bool);
        void updateState();
        void logData();
        bool getInertiaShutdown()  {return inertiaShutdown;}
        bool getKeyPosition() {return keyPosition;}
        //void changeState(State newState) {state = newState;}
        void race();
};

#endif