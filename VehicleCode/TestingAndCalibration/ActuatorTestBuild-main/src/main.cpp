#include <Arduino.h>
#include <Dashboard.h>
#include <LEDArray.h>
#include <FlexCAN_T4.h>
#include <Screen.h>


CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;
int ledPins[] = {41, 40, 39, 38, 37}; // Change these to be the pins we need

LEDArray myLED = LEDArray(ledPins);

Adafruit_7segment matrix = Adafruit_7segment();

Screen myScreen = Screen();

Actuator* testArray[] = {&myLED, &myScreen};

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
}

void loop() {

  //Serial.println("UpdateDisplay");

  myDash.updateDisplay();

  myScreen.displayTime();

  //matrix.print(100, DEC);
  //matrix.writeDisplay();

  //Serial.println("-----LOOP OVER-----");

  delay(100);

}
