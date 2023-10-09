#include "Car.h"

// CHECK: Constructor
Car::Car(const std::string logFileName, int pinForKey){
    fileName = logFileName;
    keyPin = pinForKey;

    // Initialize key pin
    pinMode(keyPin, INPUT);

    // Initialize Communication with SD card
    pinMode(chipSelect, OUTPUT);
    sd.begin(chipSelect);

    // Initialize file object and write headers
    file = sd.open(fileName, FILE_WRITE);
    file.print("Timestamp: Sensor ID: Value:");
}


// CHECK: Destructor
Car::~Car(){
    // Do we need a destructer since none of the atributes are pointers?
}


// CHECK: Method to log sensor data
void Car::logData(const SensorData data){
    // TODO: have the sensorData class have a toString method
    file.println(data.toString());
}


// TODO: Method to update the state of the car
void Car::updateState(){
    key = digitalRead(keyPin);
    // TODO: what other inputs affect the state
}


// TODO: Define difference between shutdown and emergencyShutdown
/* The difference could be that emergency shutdown is for if the 
 * car is still in motion
 */
// TODO: Method to shut down the car
void Car::shutdown(){

}

// TODO: Method for emergency shutdown
void Car::emergencyShutdown(){

}


// TODO: Method to update the motor
void Car::updateMotor(){
    // TODO: Send throttle position to motor controller
}


// CHECK: Method to check if the car is active
bool Car::checkActive(){
    return active;
}


// TODO: Method to read sensors
void Car::readSensors(){
    // TODO: maybe make this a sort of cansniff function
}