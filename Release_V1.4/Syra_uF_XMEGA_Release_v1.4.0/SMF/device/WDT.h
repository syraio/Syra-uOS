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

#define WDT_Reset()  asm("wdr")

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------

#define WDT_Wait_busy()  while((WDT.STATUS & WDT_SYNCBUSY_bm) == WDT_SYNCBUSY_bm)
	

#define WDT_isEnabled()  ((WDT.CTRL & WDT_ENABLE_bm) == WDT_ENABLE_bm)

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void WDT_Setup(WDT_PER_t per);

void WDT_Enable();

void WDT_Disable();

void WDT_SetTimeoutPeriod(WDT_PER_t tout);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void WDT_Soft_Reset();


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////