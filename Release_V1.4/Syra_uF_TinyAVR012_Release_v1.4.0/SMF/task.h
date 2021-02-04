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
//------------------- Tasks Definitions
#ifndef _MAX_TASKS_COUNT_
#warning "Maximum Tasks Count is 3"
#define _MAX_TASKS_COUNT_	3
#endif

typedef unsigned char	TASKID;

typedef struct
{
	void (*callback)(void);
	uint16_t _sleep;
}TASK_t;

volatile TASK_t _SysTasks[_MAX_TASKS_COUNT_];

volatile uint16_t _Sys_Task_Delay;

volatile uint8_t _Sys_StayAwake;

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------

#define TaskWait(ms)		_Sys_Task_Delay = ms


#define Sys_ActivateTask(id) {\
	if((id > 0) && (id <_MAX_TASKS_COUNT_))\
	{_SysTasks[id]._sleep = 0; _Sys_StayAwake = 1;}\
}

#define Sys_DeleteTask(id) {\
	if((id > 0) && (id <_MAX_TASKS_COUNT_))\
	{_SysTasks[id].callback = 0;}\
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------

void Sys_TasksInit();

TASKID Sys_CreateTask(void (*_callback)(void));

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
