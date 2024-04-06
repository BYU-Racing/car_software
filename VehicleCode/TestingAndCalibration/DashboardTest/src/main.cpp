#include <Arduino.h>
#include <Dashboard.h>
#include <LEDArray.h>
#include <FlexCAN_T4.h>
#include <Screen.h>

CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;
int pinsTemp[] = {7, 8, 9}; // Change these to be the pins we need
const byte buttonPin = 35; //ARBITUARY
LEDArray ledTemp = LEDArray(pinsTemp);

Adafruit_7segment matrix = Adafruit_7segment();

Screen myScreen = Screen();

// Actuator* testArray[] = {&myScreen, &ledTemp, &ledBat, &ledHealth};
//Actuator* testArray[] = {&myScreen};
Actuator* testArray[] = {&ledTemp};

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

  //attachInterrupt(digitalPinToInterrupt(buttonPin), sendCommand, CHANGE); This is a better solution but is bugging out
}

void loop() {

  //Serial.println("UpdateDisplay");

  myDash.updateDisplay();

  int buttonState = digitalRead(buttonPin);

  if(buttonPin == 1 && buttonState != prevState) {
    // send the start command
    Serial.println("START");
    CAN_message_t msg;
    msg.len=8;
    msg.buf[0]=0;
    msg.buf[1]=0;
    msg.buf[2]=0;
    msg.buf[3]=0;
    msg.buf[4]=0;
    msg.buf[5]=0;
    msg.buf[6]=0;
    msg.buf[7]=0;
    msg.id=192;
    myCan.write(msg);
    prevState = buttonState;
  }

  if(buttonPin == 0 && buttonState != prevState) {
    // Send stop command
    Serial.println("STOP");
    CAN_message_t msg;
    msg.len=8;
    msg.buf[0]=0;
    msg.buf[1]=0;
    msg.buf[2]=0;
    msg.buf[3]=0;
    msg.buf[4]=0;
    msg.buf[5]=0;
    msg.buf[6]=0;
    msg.buf[7]=0;
    msg.id=192;
    myCan.write(msg);
    prevState = buttonState;
  }

  // commented out for testing
  //myScreen.displayTime();
}

void sendCommand() {
  // Check switch state
  int state = digitalRead(buttonPin);

  // if switch state 1 send start command
  if(state == 1) {
    //Send start command
    Serial.println("START");
    CAN_message_t msg;
    msg.len=8;
    msg.buf[0]=0;
    msg.buf[1]=0;
    msg.buf[2]=0;
    msg.buf[3]=0;
    msg.buf[4]=0;
    msg.buf[5]=0;
    msg.buf[6]=0;
    msg.buf[7]=0;
    msg.id=192;
    myCan.write(msg);
  } else {
    //Send stop command
    Serial.println("STOP");
    CAN_message_t msg;
    msg.len=8;
    msg.buf[0]=0;
    msg.buf[1]=0;
    msg.buf[2]=0;
    msg.buf[3]=0;
    msg.buf[4]=0;
    msg.buf[5]=0;
    msg.buf[6]=0;
    msg.buf[7]=0;
    msg.id=192;
    myCan.write(msg);
  }
}