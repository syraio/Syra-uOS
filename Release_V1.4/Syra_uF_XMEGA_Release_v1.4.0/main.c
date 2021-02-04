/*	
	Author : O.NW
	dev.nww@gmail.com	
*/

//#######################################################################//
//----------------------------- Main Task -------------------------------//
//#######################################################################//
//-------------------
// Each source file should start with this header :
#include "inc.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// This function only run once, after each power up or reset.
void OnReset()
{
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// This function runs at boot time.
void OnBoot()
{	
	//===========================================
	// Write your setup instructions here.
	
	/* 
	For example : lets assume an LED connected to pin 0 of port A
		here we configure the pin 0 of port A as output.	 
	*/
	PORTA_DIRSET = PIN0_bm;	
} 

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// This function is called before the system enters sleep mode.
void OnSleep()
{
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// This is the main task.
void Main_Task()
{
	/* 
	For example : we change the status of pin 0 in port A.
	when it it 1 => turns the LED on
	when it is 0 => turns the LED off
	*/
	
	PORTA_OUTTGL = PIN0_bm;
	
		
	// Then we tell the system to run this task again after 500ms.
	TaskWait(500);
	
	
	// All Done!!
	// The LED will be blinking
	
	// Just compile and download !
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
