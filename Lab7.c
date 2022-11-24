#include "mte220.c"  // C functions needed for labs
#include <math16.h>

/*
;**********************************************************************
;
;    Filename:	    lab6.c
;    Date:          Nov 12/05
;    File Version:  3.1
;
;    Author:        C.C.W. Hulls & D.L. Wight
;
;    Copyright (c) C.C.W. Hulls, P.Eng and D.L. Wight, 2005.
;    This software can be used and modified by students, staff and
;    faculty members at the University of Waterloo for teaching or
;    research purposes, provided the authors are acknowledged.
;
;**********************************************************************
;
;    Files required:
;
;**********************************************************************
;
;    History:
;
;    3.1  Nov 12/05  use new functions and macros;
;    3.0  Nov  7/05  main code split into separate file that loads the
;                    functions needed for MTE 220
;
;    2.0  Nov  5/05  ported to C;
;
;    1.1  Oct 25/05  changed the phase of right servo to be midway
;                    through the entire cycle; enable peripheral interrupts
;                    as part of interrupt initialization
;    1.0  Oct 24/05  original release
;
;**********************************************************************
;**********************************************************************
;
;    Description:
;
;   The lab 6 code reads the IR sensors difference amplifier.  The IR
;   sensors are used for line following, so when a noticeable difference
;   is detected, the appropriate servo is turned off.
;
;**********************************************************************
*/

uns16 ServoSpeedL(uns16 percent){
    uns16 slope = (SERVO_LEFT_STOP-SERVO_1MS) / 100;
    return(SERVO_LEFT_STOP - slope*percent);
}

uns16 ServoSpeedR(uns16 percent){
    uns16 slope = (SERVO_2MS-SERVO_RIGHT_STOP) / 100;
    return((slope*percent) + SERVO_RIGHT_STOP);
}
void main(void)
{
    uns8 analog_value;  // current ADC value

    Initialization();

    // initially both servos are on
    UseServos         // (syntax of "call" is correct without () or ;)
    BothServosOn

    while (1)  // loop forever
    {
        analog_value = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp

        if ( analog_value < 0x66 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
        {
            //Turn Right
            SetLeft(ServoSpeedL(80));
            SetRight(ServoSpeedR(15));
            /* 
            //left servo only
            LeftServoOn
            RightServoOff
            */
        }
        else if ( analog_value > 0x99 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
        {
            //Turn left
                SetLeft(ServoSpeedL(15));
                SetRight(ServoSpeedR(80));
            /*
            // right servo only
            RightServoOn
            LeftServoOff
            */
        }
        else
        {
            // both servos on
            BothServosOn
        }
    }
}
