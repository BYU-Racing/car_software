#include "UARTSensor.h"
//#include <Arduino.h>


/*  UART INFO FOR TEENSY AND UART SENSORS

    PINS
    RX1     ->  0
    TX1     ->  1
    RX2     ->  7
    TX2     ->  8

    IMPORTANT DATA
    BAUD    ->  9600 (default)
    
*/

// UART recieving and transmitting pins
#define RX1 0
#define TX1 1
#define RX2 7
#define TX2 8

#define UART_ID   0x0
#define BAUD      9600
#define UART_PRIO 0x0

// FIXME constructor
 UARTSensor::UARTSensor(enum SensorID id, int freq, int prio) {

 }


// Destructor


// TODO Implement the pure virtual functions from the base class
int* readInputs() {

}

bool readyToCheck() {

}