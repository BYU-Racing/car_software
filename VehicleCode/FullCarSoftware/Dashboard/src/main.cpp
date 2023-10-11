#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  
  // TODO include pin information
  // Declare and initialize the display array of pointers
  Actuator* display[] = {
                        new Screen(), new Screen(), 
                        new LEDArray(), new LEDArray(), new LEDArray(), 
                        new Servo(), 
                        new Horn()
                        };

  // Get the starting time
  unsigned long startTime = millis();

  // Instantiate the dashboard
  Dashboard* dashboard = new Dashboard(display, startTime);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}