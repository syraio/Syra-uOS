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
//---------------------------- RTC Driver -------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>

#include "RTC.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void RTC_Setup(CLK_RTCSRC_t rclk, uint16_t period, RTC_OVFINTLVL_t int_Lvl)
{
	PR_PRGEN &= ~ PR_RTC_bm ;
	
	if (RTC_CTRL != RTC_PRESCALER_OFF_gc)
	{
		while (RTC_STATUS & RTC_SYNCBUSY_bm);
		RTC_CTRL = RTC_PRESCALER_OFF_gc ;
	}
	
	CLK_RTCCTRL = (rclk & CLK_RTCSRC_gm) | CLK_RTCEN_bm;
	
	if (RTC_CTRL != RTC_PRESCALER_OFF_gc)
	{
		while (RTC_STATUS & RTC_SYNCBUSY_bm);
		RTC_CTRL = RTC_PRESCALER_OFF_gc ;
	}
	
	RTC_PER = -1;
	RTC_COMP = -1;
	RTC_CNT = 0;
	RTC_INTCTRL = 0;
	
	while(RTC_PER != period)
	{
		while (RTC_STATUS & RTC_SYNCBUSY_bm);
		RTC_PER = period;
	}
	
	if (RTC_CTRL != RTC_PRESCALER_DIV1_gc)
	{
		while (RTC_STATUS & RTC_SYNCBUSY_bm);
		RTC_CTRL = RTC_PRESCALER_DIV1_gc;
	}
	
	RTC_INTCTRL = int_Lvl;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void RTC_Disable()
{
	if (CLK_RTCCTRL	& CLK_RTCEN_bm)
	{
		while ((RTC_CTRL & RTC_PRESCALER_gm) != RTC_PRESCALER_OFF_gc)
		{
			while (RTC_STATUS & RTC_SYNCBUSY_bm);
			RTC_CTRL = RTC_PRESCALER_OFF_gc;
		}
		
		RTC_INTCTRL = 0;
		RTC_CNT = 0;
		RTC_PER = -1;
		RTC_COMP = -1;
		
		CLK_RTCCTRL = 0;
		
		PR_PRGEN |= PR_RTC_bm;
	}	
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////