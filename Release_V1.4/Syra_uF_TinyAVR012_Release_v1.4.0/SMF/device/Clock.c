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
//------------------------- System Clock --------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/cpufunc.h>

#include "Clock.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_RC20M_Enable()
{
	CLKCTRL_OSC20MCTRLA = CLKCTRL_RUNSTDBY_bm;
	while(OSC_Status_RC20M() == 0);
}

void OSC_RC20M_Disable()
{
	CLKCTRL_OSC20MCTRLA = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_ULP32k_Enable()
{
	CLKCTRL_OSC32KCTRLA = CLKCTRL_RUNSTDBY_bm;
	while(OSC_Status_ULP32k() == 0);
}

void OSC_ULP32k_Disable()
{
	CLKCTRL_OSC32KCTRLA = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_XTAL_32k_Enable()
{
	if ((CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm) == 0)
	{
		uint8_t temp = CLKCTRL_XOSC32KCTRLA;
		temp |= CLKCTRL_RUNSTDBY_bm | CLKCTRL_ENABLE_bm;
		ccp_write_io((void*)&CLKCTRL_XOSC32KCTRLA, temp);
	}
}

void OSC_XTAL_32k_Disable()
{
	if ((CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm) != 0)
	{
		uint8_t temp = CLKCTRL_XOSC32KCTRLA;
		temp &= ~(CLKCTRL_ENABLE_bm);
		ccp_write_io((void*)&CLKCTRL_XOSC32KCTRLA, temp);
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Clock_Set(CLKCTRL_CLKSEL_t clksrc, uint8_t DivEnable, CLKCTRL_PDIV_t Prescaler)
{
	ccp_write_io((void *)&(CLKCTRL_MCLKCTRLA), clksrc);
	while (CLKCTRL_MCLKSTATUS & CLKCTRL_SOSC_bm);
	
	if (DivEnable)
	{
		CLKCTRL_MCLKCTRLA = Prescaler | CLKCTRL_PEN_bm;
	}
	else
	{
		CLKCTRL_MCLKCTRLA = 0;
	}
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

