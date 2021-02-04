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
//---------------------------------- MCU --------------------------------//
//#######################################################################//
//-------------------	Sleep Manager
#define  Set_Sleep_Mode_Standby()   {\
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;\
}

#define  Set_Sleep_Mode_Idle(mode)   {\
	SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);\
	PM->SLEEP.bit.IDLE = mode;\
}


#define  Sleep_Now()   __WFI()



//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

