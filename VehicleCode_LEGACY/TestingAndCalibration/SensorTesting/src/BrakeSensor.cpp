#include "BrakeSensor.h"
#include "Sensor.h"

/*!
 * @brief Constructor
 * Initializes the variables needed for the brake sensor to operate
 * 
 * @param id the ID that is associated with the brake sensor
 * @param waitTime how often the sensor gets read
 * @param inPin What pin on the teensy the brake sensor is connected to
 * @param dataLength TBH cannot remmber where that one is used LMAO
 * @param baseline the static reading of the preassure of the brakeline
 * @param errorMargin How large we want an error to register as
 * @return None
 */
BrakeSensor::BrakeSensor(int id, int waitTime, int inPin, int dataLength, int baseline, int errorMargin) {
    sensorID = id;
    this->waitTime = waitTime;
    previousUpdateTime = millis();
    inputPins[0] = inPin;
    this->baseline = baseline;
    this->errorMargin = errorMargin;
    this->dataLength = dataLength;
    errorBaseline = baseline; // THIS SHOULD CHANGE
    
}

/*!
 * @brief sets the can bus in the brakeSensor object so that it can communicate with
 * the motor
 * 
 * @param canIN The can object
 * @return None
 */ 
void BrakeSensor::setCan(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> canIn) {
    can2 = canIn;
}

/*!
 * @brief sends a command to the motor depending on error state and if the pedal is pressed
 * 
 * @param None
 * @return None
 */ 

void BrakeSensor::sendMotorCommand() {
    //if we are not in critical error
    if(!inCriticalError) { 
        // THIS ONLY NEEDS TO TRIGGER WHEN THROTTLE IS ALSO PAST 20% THROW but to be safe we are doing always unless bugs occur
        if(pressState == true && prevPressState == false && driveState == true) { 
            sendStopCommand();
            prevPressState = pressState;
            //PRESSING TURN OFF
        }
        else if (pressState == false && prevPressState == true && driveState == true)
        {
            //DEPRESS MOTOR ON
            sendStartCommand();
            prevPressState = pressState;
        }
    }

}


/*!
 * @brief reads the value of the brake preassure sensor and does some other commands depending on error and drive state
 * 
 * @param None
 * @return INT the reading from the sensor
 */ 
int BrakeSensor::readInputs() {
    previousUpdateTime = millis();

    brakeP = analogRead(inputPins[0]);

    if(brakeP > baseline) {
        pressState = true;
    }
    else {
        pressState = false;
    }

    if(checkError(brakeP)) {
        return -1;
    }

    if(driveState) {
        sendMotorCommand();
    }


    return brakeP;
}

/*!
 * @brief rescales data and is UNUSED
 * 
 * @param data the data that is to be rescaled
 * @return None
 */ 

int BrakeSensor::rescale(int data) {
    return data;
    // Don't know why we would need this for brake p rn
}

/*!
 * @brief builds the data from the analog sensor reading. Formats it for CAN transmission
 * 
 * @param value the value that was read from the sensor
 * @return the int array of values to send over the canLine
 */ 

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

/*!
 * @brief builds the data in the event of an error
 * 
 * @return int array for the CAN message
 */ 
int* BrakeSensor::buildError() {

    sendData[0] = 0;
    sendData[1] = 0;
    sendData[2] = driveState;
    sendData[3] = pressState;
    sendData[4] = prevPressState;
    sendData[5] = 13; // error flag ig?

    return sendData;

}
/*!
 * @brief checks if the sensor is ready to be checked
 * 
 * @return bool for if its ready
 */ 
bool BrakeSensor::readyToCheck() {
    return (waitTime <= int(millis() - previousUpdateTime));
}

/*!
 * @brief Getter for ID
 * 
 * @return int ID
 */ 
int BrakeSensor::getId() {
    return sensorID;
}

/*!
 * @brief Getter for dataLength
 * 
 * @return int DataLength
 */ 
int BrakeSensor::getDataLength() {
    return dataLength;
}

/*!
 * @brief Setter for driveState
 * 
 * @return none
 */ 
void BrakeSensor::setDriveState() {
    driveState = !driveState; // Switched on or off :)
}

/*!
 * @brief errorCheck for the brake system. Rules compliant where errors
 *  and critical errors are monitored and shut off motor if needed
 *  has some quirks due to the nature of our Brake preassure sensor but
 *  is tested to work up to rules spec
 * 
 * @param int value -> the brake preassure that is read
 * @return bool (if a perceived error is occuring or not)
 */ 
bool BrakeSensor::checkError(int value) { 
    //This function seems like it could have some bugs
    //If an abnormal or no reading is read for more than 100 msec, the motor power must be deactivated

    // IF we are not in a driving state this error checking is irrelevant
    if(!driveState) { 
        return false;
    }
    //TODO: CHECK IF THIS IS RULES COMPLIANT
    if(value <= 4) { // || value < errorBaseline - errorMargin) { //If we currently have an in error reading (techincally just need lower??)
        // If we have been in error for 100msec ENTER CRITICAL ERROR STATE
        if(inError && (millis() - timeErrorStart) > 100) { 
            sendStopCommand();
            inCriticalError = true;
            return true;
        } else if(!inError) { 
            // ^^ if we are not in error enter the error state
            inError = true;
            timeErrorStart = millis();
            return false;
        }
        return false;
    }
    //Moving out of critical error state
    else if(inCriticalError) { 
        //Remove in error
        timeErrorStart = 0;
        sendStartCommand();
        inError = false;
        inCriticalError = false;
        return false;
    }
    // Moving out of error state
    else if(inError) { 
        inError = false;
        inCriticalError = false;
        timeErrorStart = 0;
        return false;
    }
}

/*!
 * @brief Sends motor start command
 * 
 * @return none
 */ 
void BrakeSensor::sendStartCommand() {
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
/*!
 * @brief Sends motor stop command
 * 
 * @return none
 */ 
void BrakeSensor::sendStopCommand() {
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


void BrakeSensor::setLastTorque(int lastCommand) {
    this->lastTorqueCommand = lastCommand;
}