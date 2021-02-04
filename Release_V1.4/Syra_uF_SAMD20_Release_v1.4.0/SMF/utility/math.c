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
//------------------------------  Math  ---------------------------------//
//#######################################################################//
//------------------- Libraries
#include "sam.h"

#include "math.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
double _Pow(double x, uint8_t y)
{
	while((y > 0)&&(x != 0))
	{
		x *= x ;
		y--;
	}
	
	return x;
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------	Length of integer number
uint8_t _Get_NumLen(int32_t n)
{
	uint8_t x = 1;
	
	while(n > 9 )
	{
		n /= 10 ;
		x++;
	}
	
	return x;
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////



