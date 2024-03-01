#include <Arduino.h>
#include <Dashboard.h>
#include <LEDArray.h>
#include <FlexCAN_T4.h>
#include <Screen.h>


CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;
int pinsTemp[] = {7, 8, 9, 10, 11}; // Change these to be the pins we need
int pinsBat[] = {2, 3, 4, 5, 6}; // Change these to be the pins we need
int pinsHealth[] = {26, 27, 28, 29, 30}; // Change these to be the pins we need

LEDArray ledTemp = LEDArray(pinsTemp);
LEDArray ledBat = LEDArray(pinsBat);
LEDArray ledHealth = LEDArray(pinsHealth);

Adafruit_7segment matrix = Adafruit_7segment();

Screen myScreen = Screen();

Actuator* testArray[] = {&myScreen, &ledTemp, &ledTemp, &ledTemp};

Dashboard myDash(testArray, 0);


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

  //Serial.println("UpdateDisplay");

  myDash.updateDisplay();

  myScreen.displayTime();

  //matrix.print(100, DEC);
  //matrix.writeDisplay();

  //Serial.println("-----LOOP OVER-----");

  delay(10);

}
