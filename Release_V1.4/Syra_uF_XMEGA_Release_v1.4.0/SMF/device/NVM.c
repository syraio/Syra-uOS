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
//------------------------------  MCU   ---------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "NVM.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t Get_Calibration(uint8_t index)
{	
	uint8_t result;
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	result = pgm_read_byte(index);
	
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;
	
	return(result);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Get_UserSignature(uint16_t index, uint8_t* pOut, uint16_t sz)
{
	uint8_t oldCmd = NVM_CMD;
	NVM_CMD = NVM_CMD_READ_USER_SIG_ROW_gc;
	while((sz > 0) && (index <= USER_SIGNATURES_END))
	{
		*pOut = pgm_read_byte(index++);
		pOut++;
		sz--;
	}
	
	NVM_CMD = oldCmd;	
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
