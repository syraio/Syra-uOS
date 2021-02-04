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

#include "system.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
extern void OnReset();

extern void OnBoot();
extern void OnSleep();

extern void Main_Task();

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
int main(void)
{
	_CPU_Speed = STARTUP_CPU_SPEED;
	
	_sys_WakeUpTime_sec = 0;
	
	OnReset();
	
	Set_Sleep_Mode_Idle();
	
	Interrupts_EnableALL();
	
	while(1)
	{
		OSC_RC32K_Enable();
		
		Sys_TasksInit();
		Sys_CreateTask(Main_Task);
		
		OnBoot();
		
		_sys_WakeUpTime_sec = 0;
		_SysStat = SYS_STATUS_RUN;
		
		RTC_Setup(CLK_RTCSRC_RCOSC32_gc, 32, RTC_OVFINTLVL_HI_gc);
		
		TASK_t* xtask;
		
		while(_SysStat == SYS_STATUS_RUN)
		{
			_Sys_StayAwake = 0;
			
			for (uint8_t _tid = 0; _tid < _MAX_TASKS_COUNT_; _tid++)
			{
				xtask = (TASK_t*)&_SysTasks[_tid];
				
				if (xtask->callback != 0)
				{
					if (xtask->_sleep == 0)
					{
						_Sys_Task_Delay = 0;
						
						//==============================
						(*xtask->callback)();
						
						//==============================
						if (_Sys_Task_Delay > 0)
						{
							xtask->_sleep = _Sys_Task_Delay;
						}
						else
						{
							_Sys_StayAwake = 1;
						}
					}
				}
			}
			
			if (_Sys_StayAwake == 0)
			{
				Sleep_Now();
			}
		}
		
		//=================================
		RTC_Disable();
		
		OnSleep();
		
		//=================================
		if (_SysStat == SYS_STATUS_OFF)
		{
			Interrupts_DisableAll();
			Set_Sleep_Mode_PowerDown();
		}
		else if (_sys_WakeUpTime_sec > 0)
		{
			RTC_Setup(CLK_RTCSRC_RCOSC32_gc, 32768, RTC_OVFINTLVL_HI_gc);
		}
		
		while (_SysStat == SYS_STATUS_SLEEP)
		{
			Sleep_Now();
		}
	}
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

