#include <Arduino.h>
#include "input/DataCollector.h"
#include "input/AnalogSensor.h"
#include "input/UARTSensor.h"
#include "input/DigitialSensor.h"


void setup() {
  Sensor** sensors = {new AnalogSensor(),
                       new DigitalSensor()};
}

void loop() {
  
}