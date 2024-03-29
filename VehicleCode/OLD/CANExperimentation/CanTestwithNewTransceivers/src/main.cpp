#include <Arduino.h>
#include <FlexCAN_T4.h>


const int ledPin = 13;

// DEFINE GLOBAL CONSTANTS
#define DC1 6
#define DC2 5
#define DCPWM 7

CAN_message_t rmsg;

// FUNCTION PROTOTYPES
void spinMotor(int);
void stop();

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> myCan1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan2;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> myCan3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
myCan1.begin();
myCan2.begin();
myCan3.begin();
myCan1.setBaudRate(250*1000);
myCan2.setBaudRate(250*1000);
myCan3.setBaudRate(250*1000);

}

void loop() {
  // put your main code here, to run repeatedly:
CAN_message_t msg;
msg.len=1;
msg.buf[0]=254;

msg.id=2;
myCan2.write(msg);

 if ( myCan2.read(rmsg) ) 
 {
  Serial.println(rmsg.buf[0]);
  spinMotor(rmsg.buf[0]);
 }

//digitalWrite(ledPin, !digitalRead(ledPin));
//delay (500);
}


void spinMotor(int speed){
    digitalWrite(DC1, HIGH);
    digitalWrite(DC2, LOW);
    analogWrite(DCPWM, speed);
}

void stop(){
    digitalWrite(DC1, LOW);
}