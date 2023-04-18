/*
 * BYU RACING
 * Created By David Reinhardt
 * Goal: Receive signals from the CANBus to control
 *       speed of a DC Motor
 */
#include <Arduino.h>
#include <FlexCAN_T4.h>

// DEFINE GLOBAL CONSTANTS
#define DC1 6
#define DC2 5
#define DCPWM 7
CAN_message_t rmsg;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

// FUNCTION PROTOTYPES
void spinMotor(int);

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250*1000);
}

void loop() {

  // IF A CAN MESSAGE IS RECEIVED ASSIGN IT TO rmsg
  if ( can2.read(rmsg) ) {
    Serial.println(rmsg.buf[0]);
    spinMotor(rmsg.buf[0]);
  }

}

// SPINS THE MOTOR AT THE PROVIDED SPEED
void spinMotor(int speed){
  digitalWrite(DC1, HIGH);
  digitalWrite(DC2, LOW);
  analogWrite(DCPWM, speed);
}