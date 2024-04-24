#ifndef HORN_H
#define HORN_H

#include "Actuator.h"

#define SOUNDPIN 10

class Horn : public Actuator {
private:
    // Additional attributes specific to Horn
    bool hornState;

public:
// Constructor
    Horn();

// Destructor
    ~Horn();

// Additional methods for Horn
    void updateValue(SensorData&);
    void Honk();
    void hornOFF();
    void getHornState();
};

#endif // HORN_H
