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
//------------------------------  PORTS ---------------------------------//
//#######################################################################//
/*===================================== MACROS ==========================================*/

#define GPIO_CONFIG_OUT(port, mask, cfg){\
	port.DIRSET = mask;\
	PORTCFG_MPCMASK =  mask ;\
	port.PIN0CTRL = cfg ;\
}

#define GPIO_CONFIG_IN(port, mask, cfg){\
	port.DIRCLR = mask;\
	PORTCFG_MPCMASK =  mask ;\
	port.PIN0CTRL = cfg ;\
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
#define GPIO_TGL(port, mask)	port.OUTTGL = mask

#define GPIO_SET(port, mask)	port.OUTSET = mask

#define GPIO_CLR(port, mask)	port.OUTCLR = mask

#define GPIO_GET(port, mask)	(port.IN & mask)

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
#define GPIO_ENABLE_INT0(port, mask, lvl){\
	port.INTCTRL |= lvl ;\
	port.INT0MASK |= mask ;\
}

#define GPIO_ENABLE_INT1(port, mask, lvl){\
	port.INTCTRL |= lvl ;\
	port.INT1MASK |= mask ;\
}

#define GPIO_DISABLE_INT0(port){\
	port.INTCTRL &= ~(PORT_INT0LVL_HI_gc) ;\
	port.INT0MASK = 0 ;\
}

#define GPIO_DISABLE_INT1(port){\
	port.INTCTRL &= ~(PORT_INT1LVL_HI_gc) ;\
	port.INT1MASK = 0 ;\
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////