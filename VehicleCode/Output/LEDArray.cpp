#include "LEDArray.h"
#include "Actuator.h"
// Constructor
/**
 * @brief Constructor for LED Array class.
 *
 * Initializes an AnalogSensor object with specified parameters.
 * @param ledPinIn (int*) Array holding the input pins
 * Pins should be in an array from lowest to highest battery indicator 
 * ex: [0] in the array is the pin for the bottom led that blinks when battery is low
 */
LEDArray::LEDArray(int* ledPinIn) {
    this -> currentState = 0;

    this -> increment = 20; 

    this -> ledPins =  ledPinIn; // Change these as time goes on

    this-> intervalTime = 50; // MAX Blinking interval in ms for battery

    this -> lastUpdate = 0;

}


// Methods 
/**
 * @brief Updates the value for the LEDArray and Displays it.
 * @param data (const SensorData&)
 * Parses the battery data from the SensorData and then calls
 * DisplayLED to display it on the array
 * parsed should be an int between 0-100; Higher/lower values
 * do not break it but the indicator only changes within 0-100
 */
void LEDArray::updateValue(const SensorData& data) {
    // Get data from the object
    int* gotData = data.getData();

    // Parse it to the format we need

    int parsed = gotData[0]; 
    // update the LEDS

    displayLEDs(parsed);

}

/**
 * @brief displays battery percentage on LED array
 * @param value (int)
 * uses the passed in battery value expected (0-100) and displays it
 * on the led array. Blinks when value is below 10%
*/
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