#ifndef SENSORID_H
#define SENSORID_H

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


class SensorID {
private:
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


public:
    // Constructor
    SensorID();

    // CHECK: define function
    /*!
     * @brief Get the name of a sensor id
     * 
     * @param id (int) The sensor id
     * @return (std::string) The name of the sensor id
     */
    std::string getName(int id) {
        return names[id];
    }

    // CHECK: define function
    /*!
    * @brief: check sensor id values
    * 
    * @param id (int) The sensor id
    * @return (bool) True if the id matches the sensor id, false otherwise
    */
    bool checkKEY_SWITCH(int id) {
        return id == KEY_SWITCH;
    }
    bool checkBATTERY_TEMP(int id) {
        return id == BATTERY_TEMP;
    }
    bool checkCOOLANT_TEMP(int id) {
        return id == COOLANT_TEMP;
    }
    bool checkACCELERATOR_POT_1(int id) {
        return id == ACCELERATOR_POT_1;
    }
    bool checkACCELERATOR_POT_2(int id) {
        return id == ACCELERATOR_POT_2;
    }
    bool checkWHEEL_SPEED_FL(int id) {
        return id == WHEEL_SPEED_FL;
    }
    bool checkWHEEL_SPEED_FR(int id) {
        return id == WHEEL_SPEED_FR;
    }
    bool checkWHEEL_SPEED_RL(int id) {
        return id == WHEEL_SPEED_RL;
    }
    bool checkWHEEL_SPEED_RR(int id) {
        return id == WHEEL_SPEED_RR;
    }
    bool checkLED_ARRAY_1(int id) {
        return id == LED_ARRAY_1;
    }
    bool checkLED_ARRAY_2(int id) {
        return id == LED_ARRAY_2;
    }
    bool checkLED_ARRAY_3(int id) {
        return id == LED_ARRAY_3;
    }
    bool checkSEVEN_SEG_1(int id) {
        return id == SEVEN_SEG_1;
    }
    bool checkSEVEN_SEG_2(int id) {
        return id == SEVEN_SEG_2;
    }
    bool checkSERVO(int id) {
        return id == SERVO;
    }
    bool checkHORN(int id) {
        return id == HORN;
    }
    bool checkACCELEROMETER(int id) {
        return id == ACCELEROMETER;
    }
    bool checkGPS(int id) {
        return id == GPS;
    }
    bool checkDAMPER_POT_FL(int id) {
        return id == DAMPER_POT_FL;
    }
    bool checkDAMPER_POT_FR(int id) {
        return id == DAMPER_POT_FR;
    }
    bool checkDAMPER_POT_RL(int id) {
        return id == DAMPER_POT_RL;
    }
    bool checkDAMPER_POT_RR(int id) {
        return id == DAMPER_POT_RR;
    }
    bool checkSTEERING_ENCODER(int id) {
        return id == STEERING_ENCODER;
    }
    bool checkBRAKE_SWITCH(int id) {
        return id == BRAKE_SWITCH;
    }
    bool checkSTRAIN_GAUGE_1(int id) {
        return id == STRAIN_GAUGE_1;
    }
    bool checkSTRAIN_GAUGE_2(int id) {
        return id == STRAIN_GAUGE_2;
    }
    bool checkSTRAIN_GAUGE_3(int id) {
        return id == STRAIN_GAUGE_3;
    }
    bool checkSTRAIN_GAUGE_4(int id) {
        return id == STRAIN_GAUGE_4;
    }
    bool checkMOTOR_TEMP(int id) {
        return id == MOTOR_TEMP;
    }
    bool checkWALKIE_TALKIE(int id) {
        return id == WALKIE_TALKIE;
    }
    bool checkUNKNOWN(int id) {
        return id == UNKNOWN;
    }
}

#endif // SENSORID_H