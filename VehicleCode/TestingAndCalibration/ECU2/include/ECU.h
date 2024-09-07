#ifndef ECU_H
#define ECU_H

#include "SensorData.h"
#include "Throttle.h"
#include "Brake.h"


//THE ECU MONITORS EVERYTHING ABOUT THE CAR AND DECIDES WHAT SHOULD BE DONE

class ECU {
    private:


        //COMS VARS
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> comsCAN;
        FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> motorCAN;
        CAN_message_t rmsg;
        CAN_message_t motorCommand;

        //State Vars
        bool driveState = false;
        bool startFault = false;

        bool carIsGood = true;

        int driveMode = 0; //0 = Full beans, 1 = Endurance, 2 = SkidPad

        //MONITORING VARS

        //Diagnostics
        int data1Health = 0;
        int data2Health = 0;
        int data3Health = 0;
        unsigned int timer = 0;

        int wheelSpeed1Health = 0;
        int wheelSpeed2Health = 0;
        int wheelSpeed3Health = 0;
        int wheelSpeed4Health = 0;


        int dheelHealth = 0;
        
        //Start Switch
        bool startSwitchState = false;
        bool prevStartSwitchState = false;


        //Wheel Speed
        int fr_wheel_rpm;
        int fl_wheel_rpm;
        int rr_wheel_rpm;
        int rl_wheel_rpm;


        //GPS -> This may not have any real relevance
        float gps_lat;
        float gps_long;


        //Accelerometer
        float x_accel;
        float y_accel;
        float z_accel;

        float heading;

        float x_angle;
        float y_angle;
        float z_angle;

        //Steering wheel
        int steeringAngle;

        //Brake Sensor
        Brake brake;

        //Throttle Sensor
        int throttle1;
        int throttle2;
        int handoffCalVal1;
        int handoffCalVal2;

        Throttle throttle;

        bool throttle1UPDATE;
        bool throttle2UPDATE;

        int torqueCommanded;

        int throttleCode;


        //CoolantLoop
        int coolantTemp1;
        int coolantTemp2;

        //Battery

        //Motor
        bool motorState;
        bool brakeOK;
        bool throttleOK;
        bool slipOK = true;

        bool BTOveride;

        //Tractive
        bool tractiveActive;


        //Car Motion
        float slipAngle;


    public:
        ECU();

        void setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> comsCANin, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> motorCANin);

        //OVERALL CAR OPERATIONS
        void boot(); // -> initialBoot of car + diagnostics

        void run(); // -> WHILE LOOP RUNNING

        void InitialStart(); // -> HORN + COMMAND MOTOR

        void route(SensorData* data); // -> ROUTES DATA TO CORRECT SENSOR OP

        void shutdown();




        //Individual Sensor Operations
        void updateThrottle(SensorData* msg);

        void updateBrake(SensorData* msg);

        void updateSwitch(SensorData* msg);

        void updateWheelSpeed(SensorData* msg);

        void updateAccelerometer(SensorData* msg);

        void updateCoolant(SensorData* msg);

        void updateSteering(SensorData* msg);

        void updateDriveMode(SensorData* msg);


        //ACTION FUNCTIONS
        void sendMotorStartCommand();

        void sendMotorStopCommand();

        void sendMotorCommand(int torque); // -> Sends motor command needs to check for motor run conditions

        bool attemptStart(); // -> Attempts to start car if fails then goes into start fault

        void resetStartFault(); // -> Sees that all throttle / brake / switch are all zero before being able to attempt start again

        void calculateSlipAngle(); // -> Calculates slip angle for potential TC Control

        void checkBTOverride();




        void sendError(int id, int reason); // -> When a sensor gives an odd reading send a message to dashboard for the screen to display
        //A strong argument can be made for the above function to be handled by the DC

        bool runDiagnostics();

        void askForDiagnostics();

        bool reportDiagnostics();


        void calibrateThrottleMin(SensorData* data);

        void calibrateThrottleMax(SensorData* data);

        void throwError(int code);

        
};

#endif