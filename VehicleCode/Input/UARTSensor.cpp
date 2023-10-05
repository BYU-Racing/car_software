#include "UARTSensor.h"
//#include <Arduino.h>
//#include <SoftwareSerial.h


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

#define UART_ID_1   0x0
#define UART_ID_2   0x1
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

    // switch statement to initialize specific uart pins depending on given sensor id
    switch (id)
    {
    case UART_ID_1:
        Serial1.begin(BAUD); // initialize UART 1 with baud rate of 9600 bps
        break;
    case UART_ID_2:
        Serial2.begin(BAUD); // initialize UART 2 with baud rate of 9600 bps
        break;
    default:
        break;
    }
   
 }


// TODO Destructor


// read inputs from uart, save to uart_data, return pointer to uart_data
int* readInputs() {
    if (Serial1.available())     // checks to see if data is available to be read
    {
        uart_data = Serial1.read();
    }
    return &uart_data;
}

// FIXME checks to see if there is data to read
bool readyToCheck() {
    return Serial1.available();
}