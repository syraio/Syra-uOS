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
//-------------------------- Tasks Scheduler ----------------------------//
//#######################################################################//
#include "system.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Scheduler Interrupt
void RTC_Handler(void)
{	
	if (_SysStat == SYS_STATUS_RUN)
	{
		for (uint8_t i=0; i< _MAX_TASKS_COUNT_; i++)
		{
			if (_SysTasks[i]._sleep > 0)
			{
				_SysTasks[i]._sleep--;
			}
		}
	}
	else if (_sys_WakeUpTime_sec > 0)
	{
		_sys_WakeUpTime_sec--;
	}
	else
	{
		_SysStat = SYS_STATUS_RUN;
	}
	
	RTC->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_CMP0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Sys_Scheduler(SCHEDULER_MODE _mode)
{
	RTC_Disable();
			
	uint32_t tick;
		
	if (_mode == SCHEDULER_ON)
	{
		tick = 32;
	}
	else if (_mode == SCHEDULER_SLEEP)
	{
		tick = 32768;
	}
	else
	{
		Clock_Multiplexer_Disable(GCLK_CLKCTRL_ID_RTC_Val);
		Clock_Generator_Disable(SCHEDULER_CLK_GENERATOR_ID);
		return;		
	}
	
	Clock_Generator_Set(SCHEDULER_CLK_GENERATOR_ID, SRC_ULP32K, 0);
	Clock_Multiplexer_Set(GCLK_CLKCTRL_ID_RTC_Val, SCHEDULER_CLK_GENERATOR_ID);
	RTC_Mode0_Setup(tick, 1);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Sys_TasksInit()
{
	_MemoryClear((uint8_t*)_SysTasks, sizeof(_SysTasks));
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
TASKID Sys_CreateTask(void (*_callback)())
{
	for (TASKID i = 0; i < _MAX_TASKS_COUNT_; i++)
	{
		if (_SysTasks[i].callback == 0)
		{
			_SysTasks[i]._sleep = 0;
			_SysTasks[i].callback = _callback;
			return i;
		}
	}
	
	return 0xFF;
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

