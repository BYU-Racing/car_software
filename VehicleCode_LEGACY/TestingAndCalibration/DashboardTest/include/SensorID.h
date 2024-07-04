#ifndef SENSORID_H
#define SENSORID_H

#include <string>

// CHECK: Define all Sensor IDs
/*
 *  INSTRUCTIONS:
 * Copy the constants you need into your code
*/
#define KEY_SWITCH 0
#define BATTERY_TEMP 1
#define COOLANT_TEMP 2
#define ACCELERATOR_POT_1 3
#define ACCELERATOR_POT_2 4
#define WHEEL_SPEED_FL 5
#define WHEEL_SPEED_FR 6
#define WHEEL_SPEED_RL 7
#define WHEEL_SPEED_RR 8
#define LED_ARRAY_1 9
#define LED_ARRAY_2 10
#define LED_ARRAY_3 11
#define SEVEN_SEG_1 12
#define SEVEN_SEG_2 13
#define SERVO 14
#define HORN 15
#define ACCELEROMETER 16
#define GPS 17
#define DAMPER_POT_FL 18
#define DAMPER_POT_FR 19
#define DAMPER_POT_RL 20
#define DAMPER_POT_RR 21
#define STEERING_ENCODER 22
#define BRAKE_SWITCH 23
#define STRAIN_GAUGE_1 24
#define STRAIN_GAUGE_2 25
#define STRAIN_GAUGE_3 26
#define STRAIN_GAUGE_4 27
#define MOTOR_TEMP 28
#define WALKIE_TALKIE 29
#define UNKNOWN 30



// Array of sensor id names as strings

std::string names[31] = {
    "KEY_SWITCH",       // 0
    "BATTERY_TEMP",     // 1
    "COOLANT_TEMP",     // 2
    "ACCELERATOR_POT_1", // 3
    "ACCELERATOR_POT_2", // 4
    "WHEEL_SPEED_FL",   // 5
    "WHEEL_SPEED_FR",   // 6
    "WHEEL_SPEED_RL",   // 7
    "WHEEL_SPEED_RR",   // 8
    "LED_ARRAY_1",      // 9
    "LED_ARRAY_2",      // 10
    "LED_ARRAY_3",      // 11
    "SEVEN_SEG_1",      // 12
    "SEVEN_SEG_2",      // 13
    "SERVO",            // 14
    "HORN",             // 15
    "ACCELEROMETER",    // 16
    "GPS",              // 17
    "DAMPER_POT_FL",    // 18
    "DAMPER_POT_FR",    // 19
    "DAMPER_POT_RL",    // 20
    "DAMPER_POT_RR",    // 21
    "STEERING_ENCODER", // 22
    "BRAKE_SWITCH",     // 23
    "STRAIN_GAUGE_1",   // 24
    "STRAIN_GAUGE_2",   // 25
    "STRAIN_GAUGE_3",   // 26
    "STRAIN_GAUGE_4",   // 27
    "MOTOR_TEMP",       // 28
    "WALKIE_TALKIE",    // 29
    "UNKNOWN"           // 30
};

# endif // SENSORID_H