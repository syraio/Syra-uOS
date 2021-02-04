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
//---------------------------- Event System -----------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>

#include "EventSystem.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void EventSys_Setup()
{
	PR_PRGEN &= ~(PR_EVSYS_bm);	
}

void EventSys_Close()
{
	PR_PRGEN |= PR_EVSYS_bm;	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void EventSys_Set_Src(uint8_t ch, EVSYS_CHMUX_t evSrc, EVSYS_DIGFILT_t df)
{
	if (ch == 0)
	{
		EVSYS_CH0MUX = evSrc;
		EVSYS_CH0CTRL |= df & 0x07;
	}
	else if (ch == 1)
	{
		EVSYS_CH1MUX = evSrc;
		EVSYS_CH1CTRL |= df & 0x07;
	}
	else if (ch == 2)
	{
		EVSYS_CH2MUX = evSrc;
		EVSYS_CH2CTRL |= df & 0x07;
	}
	else if (ch == 3)
	{
		EVSYS_CH3MUX = evSrc;
		EVSYS_CH3CTRL |= df & 0x07;
	}
	else if (ch == 4)
	{
		EVSYS_CH4MUX = evSrc;
		EVSYS_CH4CTRL |= df & 0x07;
	}
	else if (ch == 5)
	{
		EVSYS_CH5MUX = evSrc;
		EVSYS_CH5CTRL |= df & 0x07;
	}
	else if (ch == 6)
	{
		EVSYS_CH6MUX = evSrc;
		EVSYS_CH6CTRL |= df & 0x07;
	}
	else if (ch == 7)
	{
		EVSYS_CH7MUX = evSrc;
		EVSYS_CH7CTRL |= df & 0x07;
	}	
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
