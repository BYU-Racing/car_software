#include "BrakeSensor.h"
#include "Sensor.h"



void BrakeSensor::sendMotorCommand() {

    // Send stop command if fresh pressed
    if(pressState == true && prevPressState == false) {
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
        can1.write(msg);
        prevPressState = pressState;
    }
    else if (pressState == false && prevPressState == true)
    {
        //Send motor start command
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
        prevPressState = pressState;
    }
    

    //If press state hasn't changed no command gets sent

}