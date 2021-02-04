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
//-------------------------------- Clock --------------------------------//
//#######################################################################//
typedef enum
{
	SRC_XOSC		= 0x00,
	SRC_GCLK_IO		= 0x01,
	SRC_GEN1		= 0x02,
	SRC_ULP32K		= 0x03,
	SRC_OSC32K		= 0x04,
	SRC_XOSC32K		= 0x05,
	SRC_OSC8M		= 0x06,
	SRC_DFLL48M		= 0x07
}GENERATOR_SOURCE;

void Clock_Generator_Set(uint8_t id, GENERATOR_SOURCE src, uint16_t divFactor);
void Clock_Generator_Disable(uint8_t id);

void Clock_Multiplexer_Set(uint8_t id, uint8_t gen);
void Clock_Multiplexer_Disable(uint8_t id);

void Set_Bus_Dividers(uint8_t cpuDiv, uint8_t APBxDIV);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_XTAL_Enable(uint32_t frequency);
void OSC_XTAL_Disable();

void OSC_XTAL_32k_Enable();
void OSC_XTAL_32k_Disable();

void OSC_RC32k_Enable();
void OSC_RC32k_Disable();

void OSC_RC8M_Enable(uint8_t prescaler);
void OSC_RC8M_Disable();

void OSC_DFLL_Enable(uint8_t gen, uint16_t mulFactor);
void OSC_DFLL_Disable();

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

