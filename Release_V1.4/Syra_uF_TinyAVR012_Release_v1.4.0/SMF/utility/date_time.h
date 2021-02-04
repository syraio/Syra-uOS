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

typedef uint32_t TimeStamp_t;

typedef struct
{
	int16_t year;
	int8_t month;
	int8_t day;
	int8_t h;
	int8_t m;
	int8_t s;
}DATETIME;

typedef enum 
{
	SATURDAY,
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY
}_Day_t;

typedef enum 
{
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
}_Month_t;


// Check for leap year
#define _is_Leap_Year(yr)	((yr % 400 == 0) || ((yr % 100 != 0) && (yr % 4 == 0)))

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
int8_t _getMonthDays(int8_t m, int16_t y);
int32_t _getYearDays(int16_t y);
int32_t _getYearSec(int16_t y);

TimeStamp_t _getTimestamp(DATETIME* t);

void _TimeAddSec(DATETIME* t, uint32_t sec);

int32_t _getTimeDef_Sec(DATETIME* t1, DATETIME* t2);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
