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

static int uart_Prio;           //UART priority var
static int uart_freq;           //UART frequency var
static SensorID uart_sensor_id; //UART sensor id var
static int uart_data;



// FIXME constructor
 UARTSensor::UARTSensor(enum SensorID id, int freq, int prio) {
    uart_sensor_id = id;
    uart_freq = freq;
    uart_Prio = prio;
    uart_data = 0x0;

    Serial.begin(BAUD); // initialize UART with baud rate of 9600 bps
 }


// Destructor


// TODO Implement the pure virtual functions from the base class
int* readInputs() {
    if (Serial.available())
    {
        uart_data = Serial.read();
    }
    
}

bool readyToCheck() {

}