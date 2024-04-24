#ifndef HORN_H
#define HORN_H

#include "Actuator.h"

class Horn : public Actuator {
private:
    // Additional attributes specific to Horn
    bool hornState;
    int SOUNDPIN;

public:
// Constructor
    Horn();
    Horn(int);

// Destructor
    ~Horn();

// Additional methods for Horn
    void updateValue(SensorData&);
    void Honk();
    void hornOFF();
    void getHornState();
};

#endif // HORN_H