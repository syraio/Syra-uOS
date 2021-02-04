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
//--------------------------  Time and Date -----------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>

#include "string.h"
#include "date_time.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- ok
int8_t _getMonthDays(int8_t m, int16_t y)
{
	if((y < 0) || (m < 1) || (m > 12))
	{
		return 0;
	}
	
	uint8_t monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if(_is_Leap_Year(y))
	{
		monthDays[1] = 29;
	}
	
	return monthDays[m] ;
}


int32_t _getYearDays(int16_t y)
{
	if(_is_Leap_Year(y))
	{
		return 366;
	}
	else
	{
		return 365;
	}
}

int32_t _getYearSec(int16_t y)
{
	if(_is_Leap_Year(y))
	{
		return (366 * 86400);
	}
	else
	{
		return (365 * 86400);
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- ok
TimeStamp_t _getTimestamp(DATETIME* t)
{
	if (t->year < 1970)
	{
		return 0;
	}
	
	int16_t i = 1970;
	uint32_t sec = 0 ;
	
	while(t->year > i)
	{
		if(_is_Leap_Year(i))
		{
			sec += 366;
		}
		else
		{
			sec += 365;
		}
		i++;
	}
	
	uint8_t monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if(_is_Leap_Year(i))
	{
		monthDays[1] = 29;
	}
	
	i = 1 ;
	while(i < t->month)
	{
		sec += monthDays[i-1];
		i++;
	}
	
	if (t->day > 1)
	{
		sec += (t->day - 1 ) ;
	}
	
	sec *= 24 ;
	sec += t->h ;
	sec *= 60 ;
	sec += t->m ;
	sec *= 60 ;
	sec += t->s ;
	
	return sec ;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- ok
void _TimeAddSec(DATETIME* t, uint32_t sec)
{
	uint32_t x, y, z, m;
	
	x = t->s ;
	x += sec ;
	z = x / 60 ;
	y = x - z * 60 ;
	t->s = y ;
	
	x = t->m ;
	x += z ;
	z = x / 60 ;
	y = x - z * 60 ;
	t->m = y ;
	
	x = t->h ;
	x += z ;
	z = x / 24 ;
	y = x - z * 24 ;
	t->h = y ;
	
	if (z > 0)
	{
		z += t->day ;
		
		uint8_t monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		y = t->year;
		
		if(_is_Leap_Year(y))
		{
			monthDays[1] = 29;
		}
		
		while(1)
		{
			m = monthDays[t->month - 1] ;
			if (z > m)
			{
				z -= m ;
				t->month++;
				if (t->month > 12)
				{
					t->month = 1 ;
					y++;
					
					if(_is_Leap_Year(y))
					{
						monthDays[1] = 29;
					}
					else
					{
						monthDays[1] = 28;
					}
				}
			}
			else
			{
				break;
			}
		}
		
		t->year = y;
		t->day = z;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- ok
int32_t _getTimeDef_Sec(DATETIME* t1, DATETIME* t2)
{
	int32_t x, y;

	x = _getTimestamp(t1);
	y = _getTimestamp(t2);
	
	if (x > y)
	{
		return (x - y);
	}
	else
	{
		return (y - x);
	}
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
