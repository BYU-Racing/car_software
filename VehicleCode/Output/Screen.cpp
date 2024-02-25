#include "Actuator.h"
#include "Screen.h"

/**
 * @brief Constructor for Screen class.
 *
 * Initializes a Screen object with pre defined paramters
 */

Screen::Screen() {
    this -> mode = 0; //mode 0 = time display // mode 1 = lap display
    this -> pauseTime = 10000; // ms that lap time will display at the end of the lap
    this -> modeTimeStart = 0; //Time of mode switch
    this -> timeStartTime = millis();
}

/**
 * @brief displays a passed in Lap Time on the screen
 * 
 * @param inSeconds (int) the number of seconds in the lap (LIMITED TO 2 DIGITS)
 * @param milliseconds (int) number of milliseconds in the lap (LIMITED TO 2 DIGITS)
 * 
*/
void Screen::displayLapTime(int inSeconds, int milliseconds) {
    this -> mode = 1;

    this -> modeTimeStart = millis();

    // Code that displays on the screen what the passed in laptime was

    unsigned int seconds = milliseconds;

    unsigned int minutes = inSeconds;

    //Displays it on the screen

    this->matrix.writeDigitNum(0, minutes / 10);
    this->matrix.writeDigitNum(1, minutes % 10);

    this->matrix.writeDigitNum(2, ':');

    this->matrix.writeDigitNum(3, seconds / 10);
    this->matrix.writeDigitNum(4, seconds % 10);

    matrix.drawColon(true);
    matrix.writeDisplay();

    Serial.println("SET LAPTIME TO DISPLAY");


}

/**
 * @brief displays the current runTime of the car
*/
void Screen::displayTime() {
    if(mode != 1) {
        // Display the code for the time

        Serial.println("IN DISPLAY");


        unsigned long currentTime = (millis() - this->timeStartTime) / 1000;

        unsigned int seconds = currentTime % 60;

        unsigned int minutes = currentTime / 60;


        Serial.print("SECONDS: ");
        Serial.println(seconds);

        Serial.print("MINUTES: ");
        Serial.println(minutes);

        //Displays it on the screen

        this->matrix.writeDigitNum(0, minutes / 10);
        this->matrix.writeDigitNum(1, minutes % 10);

        this->matrix.writeDigitNum(2, ':');

        this->matrix.writeDigitNum(3, seconds / 10);
        this->matrix.writeDigitNum(4, seconds % 10);

        this->matrix.drawColon(true);
        this->matrix.writeDisplay();
    };

    if(this->pauseTime <= millis() - this->modeTimeStart) { // Checks how long the mode 1 laptime display has been on and switches back to mode 0 if its been on long enough
        this->mode = 0;
    }
}

/**
 * @brief Gets the laptime from the SensorData, converts into needed format
 * Then displays it
*/

void Screen::updateValue(const SensorData& data) {

    //Pull the lap time from the sensorData object
    int* gotData = data.getData();

    int seconds = gotData[1];
    int milliseconds = gotData[2];

    displayLapTime(seconds, milliseconds);
}

/**
 * @brief displays a passed in Lap Time on the screen
 * 
 * @param myMatrix (Adafruit_7segment)
 * Sets the matrix (screen) that we are writing to for the screen
*/

void Screen::setMatrix(Adafruit_7segment myMatrix) {
    this->matrix = myMatrix;

}