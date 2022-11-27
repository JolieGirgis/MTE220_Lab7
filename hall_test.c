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

void main(void)
{
    uns8 analog_value_s;
	uns8 analog_value_h;
    Initialization();

    // initially both servos are on
    UseServos         // (syntax of "call" is correct without () or ;)

    while (1)  // loop forever
    {
        analog_value_h = AnalogConvert(ADC_HALL_EFFECT);  // Get analog value from the Hall effect sensor

		if(analog_value_h < 0x66){ // voltage above 3
			OffLED
		}
		else if(analog_value_h > 0x99){ // voltage below 2 
			OnLED
		}
    }
}

