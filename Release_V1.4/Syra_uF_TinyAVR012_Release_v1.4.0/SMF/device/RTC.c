 /*
     Copyright (C) 2015 - 2021, O.NW
 
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
 
 /*	
	Author : O.NW
	dev.nww@gmail.com	
*/
 
//#######################################################################//
//--------------------------  RTC  Driver   -----------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>

#include "RTC.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void RTC_Setup(RTC_CLKSEL_t rclk, uint16_t period, uint8_t int_Lvl)
{
	while (RTC_STATUS > 0);
	RTC_CTRLA = 0;
	
	while (RTC_STATUS > 0);
	RTC_CNT = 0;
	
	while (RTC_STATUS > 0);
	RTC_PER = period;
	
	while (RTC_STATUS > 0);
	RTC_CMP = -1;
	
	RTC_CLKSEL = rclk;
	RTC_INTCTRL = int_Lvl;
	
	while (RTC_STATUS > 0);
	RTC_CTRLA = RTC_PRESCALER_DIV1_gc | RTC_RTCEN_bm | RTC_RUNSTDBY_bm;
	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void RTC_Disable()
{
	while (RTC_STATUS & RTC_CTRLABUSY_bm);
	RTC_CTRLA = 0;
	RTC_INTCTRL = 0;
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////