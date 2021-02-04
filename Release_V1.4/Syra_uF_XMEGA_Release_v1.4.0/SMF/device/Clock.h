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
//------------------------------ Clock ----------------------------------//
//#######################################################################//

typedef enum
{
	XOSC_EXTCLK,
	XOSC_XTAL_32k,
	XOSC_XTAL_04TO2M,
	XOSC_XTAL_2TO9M,
	XOSC_XTAL_9TO12M,
	XOSC_XTAL_12TO16M
}XOSC_TYPE;


#define _SysClock_Lock()	CLK_LOCK = CLK_LOCK_bm

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
// =========
void OSC_RC32K_Enable();
uint8_t OSC_RC32K_Disable();

void OSC_RC2M_Enable();
uint8_t OSC_RC2M_Disable();

void OSC_RC32M_Enable();
uint8_t OSC_RC32M_Disable();

void OSC_XTAL_Enable(XOSC_TYPE xType);
uint8_t OSC_XTAL_Disable();

void OSC_PLL_Enable(OSC_PLLSRC_t clksrc, uint8_t pll_factor);
uint8_t OSC_PLL_Disable();

uint8_t Clock_Set(CLK_SCLKSEL_t clksrc);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

