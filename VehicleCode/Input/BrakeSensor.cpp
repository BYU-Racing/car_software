#include "BrakeSensor.h"
#include "Sensor.h"

//TODO: THIS MAY POTENTIALLY THROW ERRORS BY TURNING THE MOTOR ON BEFORE IT SHOULD BE!!!!

BrakeSensor::BrakeSensor(int id, int waitTime, int inPin, int dataLength, int baseline, int errorMargin) {
    sensorID = id;
    this->waitTime = waitTime;
    previousUpdateTime = millis();
    inputPins[0] = inPin;
    this->baseline = baseline;
    this->errorMargin = errorMargin;
    pressState = false;
    prevPressState = false;
    driveState = false;
    brakeP = 0;
    sendData = new int[8];
    this->dataLength = dataLength;
    timeErrorStart = 0;
    inError = false;
    inCriticalError = false;
}

void BrakeSensor::setCan(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIn) {
    can2 = canIn;
}

void BrakeSensor::sendMotorCommand() {
    // ADD SOME CHECK IF THE MOTOR SHOULD BE IN A RUNNING STATE
    // MAYBE HAVE THE DATACOLLECTOR LOOK FOR THE INITIAL START COMMAND AND
    // SEND THAT INTO HERE TO SET CAR STATE TO ACTIVE???

    if(!inCriticalError) { //if we are not in critical error
        if(pressState == true && prevPressState == false && driveState = true) {
            sendStopCommand();
            prevPressState = pressState;
        }
        else if (pressState == false && prevPressState == true && driveState = true)
        {
            //Send motor start command
            sendStartCommand();
            prevPressState = pressState;
        }
    //If press state hasn't changed no command gets sent
    }

}

int BrakeSensor::readInputs() {
    previousUpdateTime = millis();

    brakeP = analogRead(inputPins[0]);

    //TODO: ERROR CHECKING!

    if(brakeP > baseline) {
        pressState = true;
    }
    else {
        pressState = false;
    }

    checkError(brakeP);
    sendMotorCommand();

    return brakeP;
}

int BrakeSensor::rescale(int data) {
    return data;
    // Don't know why we would need this for brake p rn
}

int* BrakeSensor::buildData(int value) {
    // Transform value to be able to be sent in a format we can read
    // Assuming brake preassure comes in the form of a value between 0 - 9999

    // 2 digits
    sendData[0] = value / 100;

    // last 2 digits
    sendData[1] = value - ((value / 100) * 100);

    sendData[2] = driveState;

    sendData[3] = pressState;

    sendData[4] = prevPressState;

    sendData[5] = 0; //Reset error flag just in case


    return sendData;
}

int* BrakeSensor::buildError() {

    sendData[0] = 0;
    sendData[1] = 0;
    sendData[2] = driveState;
    sendData[3] = pressState;
    sendData[4] = prevPressState;
    sendData[5] = 13; // error flag ig?

    return sendData;

}

bool BrakeSensor::readyToCheck() {
    return (waitTime <= int(millis() - previousUpdateTime));
}

int BrakeSensor::getId() {
    return sensorID;
}

int BrakeSensor::getDataLength() {
    return dataLength;
}

void BrakeSensor::setDriveState() {
    driveState = !driveState; // Switched on or off :)
}

bool BrakeSensor::checkError(int value) { //This function seems like it could have some bugs
    //If an abnormal or no reading is read for more than 100 msec, the motor power must be deactivated

    if(!driveState) { // IF we are not in a driving state this error checking is irrelevant
        return true;
    }
    if(value == 0 || value < baseline) { //If we currently have an in error reading
        if(inError && (millis() - timeErrorStart) > 100) { // If we have been in error for 100msec ENTER CRITICAL ERROR STATE
            sendStopCommand();
            inCriticalError = true
            return true;
        } else if(!inError) { //if we are not in error enter the error state
            inError = true;
            timeErrorStart = millis();
            return true;
        }
        return false;
    }
    else if( inCriticalError) { //Moving out of critical error state
        //Remove in error
        timeErrorStart = 0;
        sendStartCommand();
        inError = false;
        inCriticalError = false;
        return false;
    }
    else if(inError) { // Moving out of error state
        inError = false;
        inCriticalError = false;
        timeErrorStart = 0;
        return false;
    }
}


void BrakeSensor::sendStartCommand() {
    CAN_message_t msg;
    msg.len=8;
    msg.buf[0]=0;
    msg.buf[1]=0;
    msg.buf[2]=0;
    msg.buf[3]=0;
    msg.buf[4]=0;
    msg.buf[5]=0;
    msg.buf[6]=0;
    msg.buf[7]=0;
    msg.id=192;
    can2.write(msg);
}

void BrakeSensor::sendStopCommand() {
    CAN_message_t msg;
    msg.len=8;
    msg.buf[0]=0;
    msg.buf[1]=0;
    msg.buf[2]=0;
    msg.buf[3]=0;
    msg.buf[4]=1;
    msg.buf[5]=0;
    msg.buf[6]=0;
    msg.buf[7]=0;
    msg.id=192;
    can2.write(msg);
}