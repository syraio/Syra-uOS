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
//---------------------------------- GPIO -------------------------------//
//#######################################################################//
#include "sam.h"
#include "GPIO.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void GPIO_CONFIG_MUX(uint8_t port, uint8_t pin, uint8_t cfg)
{
	if (pin & 0x01)
	{
		PORT->Group[port].PMUX[pin/2].bit.PMUXO = cfg;
	}
	else
	{
		PORT->Group[port].PMUX[pin/2].bit.PMUXE = cfg;
	}
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

