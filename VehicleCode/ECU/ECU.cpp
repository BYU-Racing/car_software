#include "ECU.h"
#include "SensorID.h"

#define HORN_PIN 10
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

#define THROTTLE_PIN_1
#define THROTTLE_PIN_2


ECU::ECU(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> comsCANin, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> motorCANin) {
    comsCAN = comsCANin;
    motorCAN = motorCANin;

    throttle = Throttle(THROTTLE_PIN_1, THROTTLE_PIN_2);

    tractiveActive = true; //For testing until we come up with a good way to read tractive
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
    digitalWrite(HORN_PIN, HIGH);
    delay(2000); // Delay for 2 seconds per rules
    digitalWrite(HORN_PIN,LOW);

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
        case ACCELERATOR_POT_1:
            updateThrottle(data);
            break;
        case ACCELERATOR_POT_2:
            updateThrottle(data);
            break;
        case BRAKE_PRESSURE:
            updateBrake(data);
            break;
        case KEY_SWITCH:
            updateSwitch(data);
            break;
    }
}




////////////////////////////////////////////////////////
////////////UPDATE FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////

void ECU::updateThrottle(SensorData* msg) {
    if(msg.getId == ACCELERATOR_POT_1) {
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

    throttleOK = !throttle.checkError(); // This is named awfully

    throttle1UPDATE = false;
    throttle2UPDATE = false;

    //Send that command to the motor
    sendMotorCommand(torqueCommanded);
}


void ECU::updateBrake(SensorData* msg) {
    brake.updateValue(msg->getData());
    brakeOK = (brake.getBrakeErrorState() == 2);
}

void ECU::updateSwitch(SensorData* msg) {
    prevStartSwitchState = startSwitchState;

    startSwitchState = (msg->getData() == 1);

    if(!startSwitchState && driveState) {
        //SHUTDOWN THE CAR!!!
        shutdown();
    }
}


///////////////////////////////////////////////
////////////ACTION FUNCTIONS///////////////////
//////////////////////////////////////////////

void ECU::sendMotorCommand(int torque) {
    //Send the command to the motor
    if(!motorState && brakeOK && throttleOK && slipOK) { //If the motor has been commanded off but should be on
        motorState = true;
        //TODO: Determine if this needs to re start the inverter
    }

    if(motorState && brakeOK && throttleOK && slipOK && !BTOveride) {
        motorCommand.id = 192;
        motorCommand.buf[0] = torque % 256;
        motorCommand.buf[1] = torque / 256;
        motorCommand.buf[2] = 0;
        motorCommand.buf[3] = 0;
        motorCommand.buf[4] = 0;
        motorCommand.buf[5] = 1; //RE AFFIRMS THE INVERTER IS ACTIVE
        motorCommand.buf[6] = 0;
        motorCommand.buf[7] = 0;
        motorCAN.send(motorCommand);
    }
    else if(motorState) { //Sends a torque Message of 0
        motorCommand.id = 192;
        motorCommand.buf[0] = 0;
        motorCommand.buf[1] = 0;
        motorCommand.buf[2] = 0;
        motorCommand.buf[3] = 0;
        motorCommand.buf[4] = 0;
        motorCommand.buf[5] = 1; //RE AFFIRMS THE INVERTER IS ACTIVE
        motorCommand.buf[6] = 0;
        motorCommand.buf[7] = 0;

        motorCAN.send(motorCommand);
    }
    return;
}


void ECU::shutdown() {
    driveState = false;
    sendMotorStopCommand();
}

bool ECU::attemptStart() {
    if(brake.getBrakeActive() && !throttle.throttleActive && !startFault && tractiveActive && carIsGood) {
        if(startSwitchState) {
            InitialStart();
            return true;
        }
        else {
            startFault = true;
            return false;
        }
    } else if(prevStartSwitchState && !startSwitchState && startFault) { // If we were in the fault position but are switching the switch off.
        startFault = false;
    }
    return false;
}


void ECU::checkBTOverride() {

    if(BTOveride && !brake.getBrakeActive() && (torqueCommanded <= BTO_OFF_THRESHOLD)) {
        BTOveride = false;
    }

    if(torqueCommanded >= BTO_ON_THRESHOLD && !BTOveride && brake.getBrakeActive()) {
        BTOveride = true;
    }
}