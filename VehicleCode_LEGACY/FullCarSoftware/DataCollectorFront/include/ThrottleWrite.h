#ifndef ThrottleWrite_H
#define ThrottleWrite_H

#include <Arduino.h>
#include <FlexCAN_T4.h>


extern FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can1;

int percentCalc1(double pot, double bias);
int getLow(int percent);
int getHigh(int percent);
int speedCalc(int pot);

#endif