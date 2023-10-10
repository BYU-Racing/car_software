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

#define UART_ID_1   0x0         //Sensor ID 1
#define UART_ID_2   0x1         //Sensor ID 2
#define BAUD        9600        //BAUD rate


static int uart_data[2];        //UART sensor data array, 0 for sensor 1, 1 for sensor 2


// FIXME constructor
 UARTSensor::UARTSensor(enum SensorID id, int freq, int prio):Sensor(id, freq, prio) {
    int priority = prio;                //UART priority var
    int waitTime = freq;                //UART wait time var
    SensorID uart_sensor_id = id;       //UART sensor id var
    int previousUpdateTime = 0;
    
    UARTSensor_init(uart_sensor_id);  // initialize uart sensors
 };

// TEST uart initilization function
void UARTSensor_init(SensorID id){
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
};


// TEST read inputs from both uart ports at the same time, save to uart_data array, return pointer to uart_data
int* UARTSensor::readInputs() {
    if (Serial1.available())     // checks to see if data is available to be read from Serial1 port
    {
        uart_data[0] = Serial1.read();
    }
    if (Serial2.available())    // checks to see if data is available to be read from serial2 port
    {
        uart_data[1] = Serial2.read();
    }
    //Update previous update time
    previousUpdateTime = int(millis());

    return uart_data;
};

// TEST checks to see if time to read values
bool readyToCheck() {
    return (waitTime <= int(millis()) - previousUpdateTime);
};