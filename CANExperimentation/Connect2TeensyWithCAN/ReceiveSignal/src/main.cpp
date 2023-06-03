/*
 * Created by David Reinhardt
 * Code to be uploaded to one of the Teensys to get them
 * to send Signals over CANBus
 * Goal: Receive a Signal over CAN and spin DC motor at 
 *       specified speed
 */
#include <Arduino.h>
#include <FlexCAN_T4.h>

// DEFINE GLOBAL CONSTANTS
#define DC1 6
#define DC2 5
#define DCPWM 7

// FUNCTION PROTOTYPES
void spinMotor(int);
void stop();


// SET UP THE CAN PROTOCOL
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

void setup() {
    // SET DC MOTOR PINS TO OUTPUT MODE
    pinMode(DC1, OUTPUT);
    pinMode(DC2, OUTPUT);
    pinMode(DCPWM, OUTPUT);
    // INITIALLY WRITE 0 TO BOTH SO THE MOTOR DOESN'T SPIN
    digitalWrite(DC1, LOW);
    digitalWrite(DC2, LOW);

    // SET UP CAN
    can1.begin();
    can1.setBaudRate(250000);

    // SET UP SERIAL MONITOR
    Serial.begin(9600);
    Serial.print("Start!");
  
}

void loop() {
    CAN_message_t msg, rmsg;
    msg.len=3;
    msg.id=1;
    msg.buf[0]=2;
    msg.buf[1]=5;
    msg.buf[2]=4;

    msg.id=2;
    can2.write(msg);
    Serial.println("Sent");

    // if(can1.read(rmsg)){
    //     Serial.println("Yes");
    //     int speed = 0;
    //     speed += rmsg.buf[0] * 100;
    //     speed += rmsg.buf[1] * 10;
    //     speed += rmsg.buf[2];
    //     spinMotor(speed);
    // }
}

void spinMotor(int speed){
    digitalWrite(DC1, HIGH);
    digitalWrite(DC2, LOW);
    analogWrite(DCPWM, speed);
}

void stop(){
    digitalWrite(DC1, LOW);
}