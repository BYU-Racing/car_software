
// TODO: Define all Sensor IDs

// CHECK: Define all Sensor IDs
enum SensorID {
    KEY_SWITCH,
    BATTERY_TEMP,
    COOLANT_TEMP,
    ACCELERATOR_POT_1,
    ACCELERATOR_POT_2,
    WHEEL_SPEED_FL,
    WHEEL_SPEED_FR,
    WHEEL_SPEED_RL,
    WHEEL_SPEED_RR,
    LED_ARRAY_1,
    LED_ARRAY_2,
    LED_ARRAY_3,
    SEVEN_SEG_1,
    SEVEN_SEG_2,
    SERVO,
    HORN,
    ACCELEROMETER,
    GPS,
    DAMPER_POT_FL,
    DAMPER_POT_FR,
    DAMPER_POT_RL,
    DAMPER_POT_RR,
    STEERING_ENCODER,
    BRAKE_SWITCH,
    STRAIN_GAUGE_1,
    STRAIN_GAUGE_2,
    STRAIN_GAUGE_3,
    STRAIN_GAUGE_4,
    MOTOR_TEMP,
    WALKIE_TALKIE_BUTTON,
    UNKNOWN
};

enum SensorID getSensorID(int index) {
    switch (index) {
        case 0: return KEY_SWITCH;
        case 1: return BATTERY_TEMP;
        case 2: return COOLANT_TEMP;
        case 3: return ACCELERATOR_POT_1;
        case 4: return ACCELERATOR_POT_2;
        case 5: return WHEEL_SPEED_FL;
        case 6: return WHEEL_SPEED_FR;
        case 7: return WHEEL_SPEED_RL;
        case 8: return WHEEL_SPEED_RR;
        case 9: return LED_ARRAY_1;
        case 10: return LED_ARRAY_2;
        case 11: return LED_ARRAY_3;
        case 12: return SEVEN_SEG_1;
        case 13: return SEVEN_SEG_2;
        case 14: return SERVO;
        case 15: return HORN;
        case 16: return ACCELEROMETER;
        case 17: return GPS;
        case 18: return DAMPER_POT_FL;
        case 19: return DAMPER_POT_FR;
        case 20: return DAMPER_POT_RL;
        case 21: return DAMPER_POT_RR;
        case 22: return STEERING_ENCODER;
        case 23: return BRAKE_SWITCH;
        case 24: return STRAIN_GAUGE_1;
        case 25: return STRAIN_GAUGE_2;
        case 26: return STRAIN_GAUGE_3;
        case 27: return STRAIN_GAUGE_4;
        case 28: return MOTOR_TEMP;
        case 29: return WALKIE_TALKIE_BUTTON;
        default: return UNKNOWN; // Invalid index, you can choose a specific value for invalid cases
    }
}