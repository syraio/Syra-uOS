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

#define GPIO_CONFIG_OUT(port, pin, cfg) {\
	PORT->Group[port].DIRSET.reg = (0x01U << pin);\
	PORT->Group[port].PINCFG[pin].reg = cfg;\
}

#define GPIO_CONFIG_IN(port, pin, cfg) {\
	PORT->Group[port].DIRCLR.reg = (0x01U << pin);\
	PORT->Group[port].PINCFG[pin].reg = PORT_PINCFG_INEN | cfg;\
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
#define GPIO_TGL(port, mask)	PORT->Group[port].OUTTGL.reg = mask

#define GPIO_SET(port, mask)	PORT->Group[port].OUTSET.reg = mask

#define GPIO_CLR(port, mask)	PORT->Group[port].OUTCLR.reg = mask

#define GPIO_GET(port, mask)	(PORT->Group[port].IN.reg & mask)

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------

void GPIO_CONFIG_MUX(uint8_t port, uint8_t pin, uint8_t cfg);



//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

