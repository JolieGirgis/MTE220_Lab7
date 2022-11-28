#include "mte220.c"  // C functions needed for labs

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

//;**********************************************************************
void LED_Blink(int time){
	int i = 0;
	while(i < time){
		OnLED
		LongDelay(3.5);
		OffLED
		LongDelay(3.5);
		i++;
	}
}

void LED_on(int time){
	OnLED
	LongDelay(time);
	OffLED
}

void main(void)
{
    uns8 analog_value;  // current ADC value for IR sensor
    uns8 analog_value_hall; // current ADC value for hall effect sensor
    uns8 blinked = 0; // indicate whether LED has blinked before  
    uns8 flashed = 0; // indicates whether LED has flashed for 7 seconds before
    
    Initialization();

    UseServos         

    while (1)  // loop forever
    {
        WaitForButton();  // wait until the button is pushed

        analog_value_ir = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp

	analog_value_hall =  AnalogConvert(ADC_HALL_EFFECT); // get analog value from the hall effect sensor
		
	// Blink LED for 7 seconds if hall effect sensor below 0 gauss (2V)
	if( analog_value_hall < 0x66 && blinked == 0)
	{
		BothServosOff
		LED_Blink(7); // blink LED for 7 seconds
		blinked++;
	}
	// Turn LED on for 7 seconds if hall effect sensor above 0 gauss (3V)
	else if (analog_value_hall > 0x99 && flashed == 0)
	{
		BothServosOff
		LED_on(49) // turn LED on for 7 seconds
		flashed++;
	}
	else
	{
		if (analog_value_hall > 0x66 && analog_value_hall < 0x99)
		{
			blinked = 0;
			flashed = 0;
		}

		if ( analog_value_ir < 0x66 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
		{
			// left servo only
			LeftServoOn
			RightServoOff
		}
		else if ( analog_value_ir > 0x99 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
		{
		 	// right servo only
		 	RightServoOn
			LeftServoOff
		}
		else
		{
		 	// both servos on
		 	BothServosOn
		}
	}
    }
}

