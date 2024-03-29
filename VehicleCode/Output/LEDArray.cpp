#include "LEDArray.h"
#include "Actuator.h"
// Constructor
/**
 * @brief Constructor for LED Array class.
 *
 * Initializes an AnalogSensor object with specified parameters.
 * @param ledPinIn (int*) Array holding the input pins
 * Pins should be in an array in the format {RED, GREEN, BLUE}
 */
LEDArray::LEDArray(int* ledPinIn) {
    this -> currentState = 0;
    this -> increment = 20; 
    this -> ledPins =  ledPinIn; // Change these as time goes on
    this-> intervalTime = 50; // MAX Blinking interval in ms for battery
    this -> lastUpdate = 0;
}


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

    //IF BATTERY STATE OF CHARGE IT SHOULD BE 0-100
    int value = gotData[0]; 
    int flag = gotData[1];

    //Possibly check an identifer in the message to send it to
    //the correct display function

    if(flag == 1) { // Flag 0 is for Battery Percentage
        displayLEDsPerc(value);
    }
    else if(flag == 2) {
        displayLEDsTemp(value); //Flag 2 is for Battery Temp
    }
    
}

/**
 * @brief creates a helper struct for the battery percentage
*/
struct RGBColor {
    int R;
    int G;
    int B;
};

/**
 * @brief creates a helper struct for the battery percentage
 * @param value (int)
 * integer bewteen 10-100 (Will also work with any value but is intended for 10-100)
 * converts that to RGB for gradient from G to R based on the passed in battery percentage
*/
RGBColor mapValueToRGB(int value) {
    RGBColor color;
    
    // Ensure the value is within the valid range
    value = std::min(160, std::max(40, value));
    
    // Calculate the interpolation factor
    double factor = (value - 40) / 120.0;
    
    // Interpolate between red and yellow
    color.R = 255;
    color.G = static_cast<int>(255 * factor);
    color.B = 0;
    
    return color;
}

/**
 * @brief displays battery percentage on LED array
 * @param value (int)
 * uses the passed in battery value expected (0-200) and displays it
 * on the led array. Blinks when value is below 10% (20)
*/
void LEDArray::displayLEDsPerc(int value) {
    // Whatever value indicates that we need to blink
    if(value < 20 && (millis() - this->lastUpdate) >= this->intervalTime) { 
        if(this -> currentState == 0) { // 0 = LED OFF
            // Turn on blink LED
            digitalWrite(ledPins[0], 255); //IS 254 right for the max?
            digitalWrite(ledPins[1], 0);
            digitalWrite(ledPins[2], 0);
            this -> currentState = 1;
            this->lastUpdate = millis();
        }
        else {
            // Turn off blink LED
            digitalWrite(ledPins[0], 0);
            digitalWrite(ledPins[1], 0);
            digitalWrite(ledPins[2], 0);
            this -> currentState = 0;
        }

    }
    else {
        RGBColor color = mapValueToRGB(value);

        digitalWrite(ledPins[0], color.R); //WRITE RED
        digitalWrite(ledPins[1], color.G); //WRITE GREEN
        digitalWrite(ledPins[2], color.B); //WRITE BLUE
    }
}

/**
 * @brief displays battery temp on LED array
 * @param value (int)
 * uses the passed in battery health value expected and displays it in colors on the LED.
 *  Blue = Below expected operating temp
 *  Green = Within expected operating temp
 *  Yellow = Approaching too high
 *  Red = Exceeding expected operating temperatures
*/
void LEDArray::displayLEDsTemp(int value) {
    //Create a new mapping
    int bottomRange = 25;
    int upperBound = 55;

    if(value <= bottomRange) { //Write BLUE
        digitalWrite(ledPins[0], 0); //RED
        digitalWrite(ledPins[1], 0); //GREEN
        digitalWrite(ledPins[2], 255);  //BLUE
    }
    else if((value > bottomRange) && (value < upperBound - 5)) { //Write Green
        digitalWrite(ledPins[0], 0); //RED
        digitalWrite(ledPins[1], 255); //GREEN
        digitalWrite(ledPins[2], 0); //BLUE
    }
    else if((value >= upperBound - 5) && (value < upperBound)) { //Write Yellow
        digitalWrite(ledPins[0], 255); //RED
        digitalWrite(ledPins[1], 255); //GREEN
        digitalWrite(ledPins[2], 0); //BLUE
    }
    else {
        digitalWrite(ledPins[0], 255); //RED
        digitalWrite(ledPins[1], 0); //GREEN
        digitalWrite(ledPins[2], 0); //BLUE 
    } 
}

