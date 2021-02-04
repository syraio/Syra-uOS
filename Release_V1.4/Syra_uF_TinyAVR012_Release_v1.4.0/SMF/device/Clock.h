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

#define OSC_Status_RC20M()   (CLKCTRL.MCLKSTATUS & CLKCTRL_OSC20MS_bm)

#define OSC_Status_ULP32k()   (CLKCTRL.MCLKSTATUS & CLKCTRL_OSC32KS_bm)

#define OSC_Status_XTAL32k()   (CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm)


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
// =========
void OSC_RC20M_Enable();
void OSC_RC20M_Disable();

void OSC_ULP32k_Enable();
void OSC_ULP32k_Disable();

void OSC_XTAL_32k_Enable();
void OSC_XTAL_32k_Disable();

void Clock_Set(CLKCTRL_CLKSEL_t clksrc, uint8_t DivEnable, CLKCTRL_PDIV_t Prescaler);


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

