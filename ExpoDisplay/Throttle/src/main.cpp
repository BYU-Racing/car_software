/*
 * BYU RACING
 * Created By David Reinhardt
 * Authors    Tyson Danby
 * Goal: Send signals containing throttle position 
 *       over the CANBus
 */
#include <Arduino.h>
#include <FlexCAN_T4.h>

// GLOBAL VARIABLES
#define POT A0
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

// CALIBRATION CONSTANTS
const float BIAS = 200;
const float RANGE = 800 - BIAS;

// FUNCTION PROTOTYPES
int speedCalc(int);

void setup() {
  // SET UP SERIAL MONITOR
  Serial.begin(9600);
  Serial.println("Start");

  // SET UP CAN
  can2.begin();
  can2.setBaudRate(250000);
}

void loop() {
  
  // CREATE AND SEND THE CAN MESSAGE
  CAN_message_t msg;
  msg.len=1; // SETS MESSAGE LENGTH
  msg.buf[0]=speedCalc(analogRead(POT)); // SEND SPEED VALUE
  msg.id=2;
  can2.write(msg);

}

// FUNCTION TO CONVERT THROTTLE POSITION TO PWM VALUE FOR DC MOTOR
int speedCalc(int pot){
  // IF VALUE OF POTENTIOMETER IS BELOW OUR TESTES
  // VALUE FOR ZERO RETURN 0
  if(pot < BIAS) return 0;

  // CALCULATE  THROTTLE PRESSED PERCENTAGE
  float percent = (pot - BIAS) / RANGE;

  // USE VALUES FOUND FOR DC MOTOR TO GET 
  // PWM VALUE BASED ON THROTTLE POSITION
  float speed = percent * 109 + 145;

  // IF VALUE EXCEEDS MAX PWM VALUE RETURN 254
  if(speed > 254) return 254;

  else return (int)speed;
}