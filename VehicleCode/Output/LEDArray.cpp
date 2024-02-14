#include "LEDArray.h"
#include "Actuator.h"
// Constructor

LEDArray::LEDArray(int* ledPinIn) {
    this -> currentState = 0;

    this -> increment = 20; 

    this -> ledPins =  ledPinIn; // Change these as time goes on

    this-> intervalTime = 50; // MAX Blinking interval in ms for battery

    this -> lastUpdate = 0;

}


// Methods 

void LEDArray::updateValue(const SensorData& data) {
    // Get data from the object
    int* gotData = data.getData();

    // Parse it to the format we need

    int parsed = gotData[0]; 
    // update the LEDS

    displayLEDs(parsed);

}

void LEDArray::displayLEDs(int value) {

    if(value < 10 && (millis() - this->lastUpdate) >= this->intervalTime) { // Whatever value indicates that we need to blink
        if(this -> currentState == 0) { // 0 = LED OFF
            // Turn on blink LED
            digitalWrite(ledPins[0], HIGH);
            this -> currentState = 1;
            this->lastUpdate = millis();
        }
        else {
            // Turn off blink LED
            digitalWrite(ledPins[0], LOW);
            this -> currentState = 0;
        }

    }
    else {
        for (int i = 0; i < 5; i++) {
            if (i <= value / this->increment) {
                digitalWrite(this->ledPins[i], HIGH);
            }
            else {
                digitalWrite(this->ledPins[i], LOW);
            }
        }
    }
}