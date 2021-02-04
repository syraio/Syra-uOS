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
//------------------------------ Memory ---------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "memory.h"
 
///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// this function sets all bytes specified by sz of memory m in the RAM to zero.
// m is a pointer for the memory in RAM.
// sz is the number of bytes to be zero.
void _MemoryClear(uint8_t* m, uint16_t sz)
{
	while(sz > 0)
	{
		*m = 0;
		m++;
		sz--;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// this function copy data from RAM to RAM.
// mi is a pointer for the input memory in RAM.
// mo is a pointer for the output memory in RAM.
// sz is the number of bytes to copy.
void _MemoryCopy(uint8_t* mo, uint8_t* mi, uint16_t sz)
{
	while(sz > 0)
	{
		*mo = *mi;
		mo++;
		mi++;
		sz--;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// this function copy data from flash memory to RAM.
// mi is a pointer for the input memory in flash.
// mo is a pointer for the output memory in RAM.
// sz is the number of bytes to copy.
void _MemoryCopy_P(uint8_t* mo, const uint8_t* mi, uint16_t sz)
{
	while(sz > 0)
	{
		*mo = pgm_read_byte(mi);
		mo++;
		mi++;
		sz--;
	}
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
// this function compare "m1" with "m2", and return true if "sz" number of bytes is equal.
// m1 and m2 are pointers in RAM.
// sz is the number of bytes to compare.
uint8_t _MemoryComp(uint8_t* m1, uint8_t* m2, uint16_t sz)
{
	while(sz > 0)
	{
		if(*m1 != *m2)
		{
			return 0;
		}
		
		m1++;
		m2++;
		sz--;
	}
	
	return 1;
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

