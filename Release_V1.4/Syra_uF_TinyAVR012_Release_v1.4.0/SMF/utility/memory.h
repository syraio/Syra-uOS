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

void _MemoryClear(uint8_t* m, uint16_t sz);

void _MemoryCopy(uint8_t* mo, uint8_t* mi, uint16_t sz);

void _MemoryCopy_P(uint8_t* mo, const uint8_t* mi, uint16_t sz);

uint8_t _MemoryComp(uint8_t* m1, uint8_t* m2, uint16_t sz);


// #define _Clear_var(x)	 _MemoryClear((uint8_t*)&x, sizeof(x))
// #define _Clear_ptr(x)	 _MemoryClear((uint8_t*)x, sizeof(x))


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
