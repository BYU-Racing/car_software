#include <Arduino.h>
#include <Dashboard.h>
#include <LEDArray.h>
#include <FlexCAN_T4.h>
#include <Screen.h>

CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;
int pinsTemp[] = {14, 15, 16}; // Change these to be the pins we need
int pinsBat[] = {17, 18, 19};
LEDArray ledTemp = LEDArray(pinsTemp);
LEDArray ledBat = LEDArray(pinsBat);

Adafruit_7segment matrix = Adafruit_7segment();

Screen myScreen = Screen();

Actuator* testArray[] = {&myScreen, &ledTemp, &ledBat};

Dashboard myDash(testArray, 0);

int prevState = 0;


void setup() {
  // put your setup code here, to run once:
  //Setup Serial Port
  Serial.begin(9600);
  Serial.println("STARTED");

  myCan.begin();
  myCan.setBaudRate(250000);

  matrix.begin(0x70);
  myScreen.setMatrix(matrix);

  myDash.setCAN(myCan);
  myDash.resetTimeZero(millis());
}

void loop() {

  myDash.updateDisplay();

}