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
//-------------------------------- WDT ----------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/cpufunc.h>

#include "WDT.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void WDT_Setup(WDT_PER_t per)
{
	WDT_SetTimeoutPeriod(per);
	WDT_Enable();
	WDT_Reset();
}

void WDT_Enable()
{
	uint8_t temp = WDT_CTRL | WDT_ENABLE_bm | WDT_CEN_bm;
	
	ccp_write_io((uint8_t *)&WDT_CTRL, temp);
	WDT_Wait_busy();
}

void WDT_Disable()
{
	uint8_t temp = WDT_CTRL | WDT_CEN_bm;
	temp &= (~WDT_ENABLE_bm);
	
	ccp_write_io((uint8_t *)&WDT_CTRL, temp);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void WDT_SetTimeoutPeriod(WDT_PER_t tout)
{
	uint8_t temp = WDT_CTRL & WDT_ENABLE_bm;
	temp |= tout | WDT_CEN_bm ;
	ccp_write_io((uint8_t *)&WDT_CTRL, temp);
	WDT_Wait_busy();
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Reset MCU via Watchdog.
void WDT_Soft_Reset()
{
	uint8_t temp;
	
	temp = WDT_PER_8CLK_gc | WDT_ENABLE_bm | WDT_CEN_bm;
	ccp_write_io((uint8_t *)&WDT_CTRL, temp);
	WDT_Wait_busy();
	
	temp = WDT_WPER_8KCLK_gc |  WDT_WEN_bm | WDT_WCEN_bm;
	ccp_write_io((uint8_t *)&WDT_WINCTRL, temp);
	WDT_Wait_busy();
	
	WDT_Reset();
	
	while(1){}
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////







