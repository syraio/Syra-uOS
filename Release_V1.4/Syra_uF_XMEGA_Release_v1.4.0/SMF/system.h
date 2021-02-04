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
//------------------------------- System --------------------------------//
//#######################################################################//
//------------------- 
#include "../config.h"

#include "device/index.h"
#include "utility/index.h"

#include "task.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
typedef enum
{
	SYS_STATUS_RUN,
	SYS_STATUS_REBOOT,
	SYS_STATUS_SLEEP,
	SYS_STATUS_OFF
}SYSTEM_STATUS;
volatile SYSTEM_STATUS _SysStat;

volatile uint32_t _sys_WakeUpTime_sec;

#define Sys_Reboot()		_SysStat = SYS_STATUS_REBOOT
#define Sys_Shutdown()		_SysStat = SYS_STATUS_OFF

#define Sys_Sleep(x)		{_SysStat = SYS_STATUS_SLEEP; _sys_WakeUpTime_sec = x;}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
volatile uint32_t _CPU_Speed;

#define  Set_CpuSpeed(x)	_CPU_Speed = x


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
