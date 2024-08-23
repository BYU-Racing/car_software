#include "ECU.h"
#include "FlexCAN_T4.h"
#include "Throttle.h"
#include "Brake.h"

#define HORN_PIN 12
#define BRAKE_THRESHOLD 50

#define MIN_THROTTLE_OUTPUT 0
#define MAX_THROTTLE_OUTPUT 5000

#define MIN_THROTTLE_READ_POS 36
#define MAX_THROTTLE_READ_POS 500

#define MIN_THROTTLE_READ_NEG 679
#define MAX_THROTTLE_READ_NEG 962
#define THROTTLE_ERROR_TOL 1600
#define THROTTLE_MAINTAIN_TOL 2
#define THROTTLE_NOISE_REDUCTION_THRESHOLD 60

#define BTO_OFF_THRESHOLD 120
#define BTO_ON_THRESHOLD 300

#define THROTTLE1_ID 3
#define THROTTLE2_ID 4
#define BRAKE_ID 2
#define KEY_ID 1

#define CALIBRATE_THROTTLE_MIN_ID 104
#define CALIBRATE_THROTTLE_MAX_ID 105


ECU::ECU() {
    throttle = Throttle();
    brake = Brake();

    tractiveActive = true; //For testing until we come up with a good way to read tractive
    pinMode(HORN_PIN, OUTPUT);
}

void ECU::setCAN(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> comsCANin, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> motorCANin) {
    comsCAN = comsCANin;
    motorCAN = motorCANin;
}

//Initial Diagnostics
void ECU::boot() {
    carIsGood = runDiagnostics();
}

bool ECU::runDiagnostics() {
    askForDiagnostics(); //Starts Diagnostic Process

    return (reportDiagnostics()); // Reads Diagnostics
}

void ECU::askForDiagnostics() {
    //Just send the CAN message out for diagnositcs
    rmsg.id = 100; // DIAGNOSTIC ID

    rmsg.len = 8;

    rmsg.buf[0] = 0;
    rmsg.buf[1] = 0;
    rmsg.buf[2] = 0;
    rmsg.buf[3] = 0;
    rmsg.buf[4] = 0;
    rmsg.buf[5] = 0;
    rmsg.buf[6] = 0;
    rmsg.buf[7] = 0;

    // Write on the comsCAN
    comsCAN.write(rmsg);
}

bool ECU::reportDiagnostics() {
    timer = millis();
    // No handoff should be needed to dashboard since it is on comsCAN line
    while(millis() - timer <= 100) {
        if(comsCAN.read(rmsg)) {
            if(rmsg.id == 101) {
                data1Health = rmsg.buf[0];
            }
            if(rmsg.id == 102) {
                data2Health = rmsg.buf[0];
            }
            if(rmsg.id == 103) {
                data3Health = rmsg.buf[0];
            }
        }
    }

    return (data1Health >= 2 && data2Health >= 2 && data3Health >= 2);
}

//START + HORN
void ECU::InitialStart() {
    Serial.println("INITIAL START ACHIEVED");
    digitalWrite(HORN_PIN, HIGH);
    delay(2000); // Delay for 2 seconds per rules
    digitalWrite(HORN_PIN,LOW);

    //Send the driveState command for the dash
    rmsg.id=203;
    rmsg.buf[0]=1;
    rmsg.buf[1]=0;
    rmsg.buf[2]=0;
    rmsg.buf[3]=0;
    rmsg.buf[4]=0;
    rmsg.buf[5]=0;
    rmsg.buf[6]=0;
    rmsg.buf[7]=0;

    comsCAN.write(rmsg);
    //Start the motor
    driveState = true;

    sendMotorStartCommand();
}


//INGESTS MESSAGES AND ROUTES THEM (LOOP FUNCTION)
void ECU::run() {
    if(!driveState) {
        //TODO: SHOULD THIS SEND A START FAULT NOTICE TO THE DRIVER???
        attemptStart();
        if(startFault) {
            //SEND MESSAGE TO DRIVER SCREEN ABOUT START FAULT!!
            throwError(5);
        }
    }

    // read coms CAN line 
    if(comsCAN.read(rmsg)) {
        SensorData* msg = new SensorData(rmsg);
        route(msg);
    }

    if(!carIsGood) { // If something bad happened shutdown the car again just in case
        shutdown();
    }
}

//ROUTES DATA (READS ID AND SENDS IT TO THE RIGHT FUNCTION)
void ECU::route(SensorData* data) {
    switch (data->getId()) {
        case THROTTLE1_ID:
            updateThrottle(data);
            break;
        case THROTTLE2_ID:
            updateThrottle(data);
            break;
        case BRAKE_ID:
            updateBrake(data);
            break;
        case KEY_ID:
            updateSwitch(data);
            break;
        case CALIBRATE_THROTTLE_MIN_ID:
            calibrateThrottleMin(data);
            break;
        case CALIBRATE_THROTTLE_MAX_ID:
            calibrateThrottleMax(data);
            break;
    }
}




////////////////////////////////////////////
////////////UPDATE FUNCTIONS////////////////
////////////////////////////////////////////

void ECU::updateThrottle(SensorData* msg) {
    if(msg->getId() == THROTTLE1_ID) {
        throttle.setThrottle1(msg->getData());
        throttle1UPDATE = true;
    } else {
        throttle.setThrottle2(msg->getData());
        throttle2UPDATE = true;
    }
    if(!throttle1UPDATE || !throttle2UPDATE) { // exits if both haven't been updated
        return;
    }

    torqueCommanded = throttle.calculateTorque();
    if(torqueCommanded < 0) {
        torqueCommanded = 0;
    }

    throttleCode = throttle.checkError();

    //Calling check error twice could accidentally count a mismatch twice so we want to carry the value over
    throttleOK = (throttleCode == 0);
    
    if(!throttleOK) {
        throwError(throttleCode);
    }

    throttle1UPDATE = false;
    throttle2UPDATE = false;

    //Send that command to the motor
    sendMotorCommand(torqueCommanded);
}


void ECU::updateBrake(SensorData* msg) {
    brake.updateValue(msg->getData());
    brakeOK = (brake.getBrakeErrorState() != 2); 

    if(!brakeOK) {
        throwError(4);
    }
}

void ECU::updateSwitch(SensorData* msg) {
    prevStartSwitchState = startSwitchState;

    startSwitchState = (msg->getData()[0] == 1);

    if(!startSwitchState && driveState) {
        //SHUTDOWN THE CAR!!!
        shutdown();
    }
}


/////////////////////////////////////////
////////////ACTION FUNCTIONS/////////////
/////////////////////////////////////////


//STOP/START BASE FUNCTIONS

void ECU::sendMotorStartCommand() {
    Serial.println("Motor start command sent");
    motorState = true;
    return;
}

void ECU::sendMotorStopCommand() {
    //Serial.println("Motor stop command sent");
    motorState = false;
    return;
}

void ECU::sendMotorCommand(int torque) {
    //Send the command to the motor
    if(!motorState && brakeOK && throttleOK && slipOK && driveState) { //If the motor has been commanded off but should be on
        motorState = true;
        //TODO: Determine if this needs to re start the inverter
    }
    if(driveState) {
        checkBTOverride();
    }

    if(motorState && brakeOK && throttleOK && !BTOveride && driveState) {
        Serial.println(torqueCommanded);
        motorCommand.id = 192;
        motorCommand.buf[0] = torque % 256;
        motorCommand.buf[1] = torque / 256;
        motorCommand.buf[2] = 0;
        motorCommand.buf[3] = 0;
        motorCommand.buf[4] = 0;
        motorCommand.buf[5] = 1; //RE AFFIRMS THE INVERTER IS ACTIVE
        motorCommand.buf[6] = 0;
        motorCommand.buf[7] = 0;
        motorCAN.write(motorCommand);
    }
    else if(motorState || !driveState) { //Sends a torque Message of 0
        Serial.println(0);
        motorCommand.id = 192;
        motorCommand.buf[0] = 0;
        motorCommand.buf[1] = 0;
        motorCommand.buf[2] = 0;
        motorCommand.buf[3] = 0;
        motorCommand.buf[4] = 0;
        motorCommand.buf[5] = 1; //RE AFFIRMS THE INVERTER IS ACTIVE
        motorCommand.buf[6] = 0;
        motorCommand.buf[7] = 0;
        motorCAN.write(motorCommand); 
    }

    return;
}


void ECU::shutdown() {
    driveState = false;
    BTOveride = false;
    Serial.println("SHUTDOWN");
    rmsg.id=203;
    rmsg.buf[0]=0;
    rmsg.buf[1]=0;
    rmsg.buf[2]=0;
    rmsg.buf[3]=0;
    rmsg.buf[4]=0;
    rmsg.buf[5]=0;
    rmsg.buf[6]=0;
    rmsg.buf[7]=0;

    comsCAN.write(rmsg);
    sendMotorStopCommand();
}


bool ECU::attemptStart() {
    carIsGood = true;
    if(brake.getBrakeActive() && !startFault && tractiveActive && carIsGood) {
        if(startSwitchState) {
            InitialStart();
            return true;
        }
    } else if(prevStartSwitchState && !startSwitchState && startFault) { // If we were in the fault position but are switching the switch off.
        startFault = false;
    }
    if(startSwitchState && !prevStartSwitchState) { // If we just flicked on the switch and did not satisfy the start conditions
        startFault = true;
        Serial.println("Start Faulted");
    }
    return false;
}


void ECU::checkBTOverride() {

    if(BTOveride && !brake.getBrakeActive() && (torqueCommanded <= BTO_OFF_THRESHOLD)) {
        BTOveride = false;
        Serial.println("BTO Set");
    }

    if(torqueCommanded >= BTO_ON_THRESHOLD && !BTOveride && brake.getBrakeActive()) {
        BTOveride = true;
        Serial.println("BTO Released");
    }
}


void ECU::calibrateThrottleMin(SensorData* data) {
    //First 2 are t1 min Second 2 are t2 min
    handoffCalVal1 = (data->getData()[0] * 100) + data->getData()[1];
    handoffCalVal2 = (data->getData()[2] * 100) + data->getData()[3];

    throttle.setCalibrationValueMin(handoffCalVal1, handoffCalVal2);
}

void ECU::calibrateThrottleMax(SensorData* data) {
    handoffCalVal1 = (data->getData()[0] * 100) + data->getData()[1];
    handoffCalVal2 = (data->getData()[2] * 100) + data->getData()[3];

    throttle.setCalibrationValueMax(handoffCalVal1, handoffCalVal2);
}


void ECU::throwError(int code) {
    rmsg.id = 200; // DIAGNOSTIC ID

    rmsg.len = 8;

    rmsg.buf[0] = code;
    rmsg.buf[1] = 0;
    rmsg.buf[2] = 0;
    rmsg.buf[3] = 0;
    rmsg.buf[4] = 0;
    rmsg.buf[5] = 0;
    rmsg.buf[6] = 0;
    rmsg.buf[7] = 0;
    // Send the error code to the Dashboard
    comsCAN.write(rmsg);
}