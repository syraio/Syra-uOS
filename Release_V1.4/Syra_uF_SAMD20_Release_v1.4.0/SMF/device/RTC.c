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
//--------------------------------- RTC ---------------------------------//
//#######################################################################//
#include "sam.h"

#include "RTC.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void RTC_Disable()
{
	if (RTC->MODE0.CTRL.bit.ENABLE)
	{
		RTC->MODE0.CTRL.bit.ENABLE = 0;
		while (RTC->MODE0.STATUS.bit.SYNCBUSY);
	}
		
	NVIC_DisableIRQ(RTC_IRQn);
	
	PM->APBAMASK.reg &= ~(PM_APBAMASK_RTC);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void RTC_Mode0_Setup(uint32_t cmp, uint8_t intEnable)
{
	PM->APBAMASK.reg |= PM_APBAMASK_RTC;
	
	RTC->MODE0.CTRL.reg = 0;
	while (RTC->MODE0.STATUS.bit.SYNCBUSY);
	
	RTC->MODE0.CTRL.reg = RTC_MODE0_CTRL_PRESCALER_DIV1
							| RTC_MODE0_CTRL_MODE_COUNT32
							| RTC_MODE0_CTRL_MATCHCLR;
	
	while (RTC->MODE0.STATUS.bit.SYNCBUSY);
	
	RTC->MODE0.COUNT.reg = 0;
	while (RTC->MODE0.STATUS.bit.SYNCBUSY);
	
	RTC->MODE0.COMP[0].reg = cmp;
	while (RTC->MODE0.STATUS.bit.SYNCBUSY);
	
	if (intEnable)
	{
		RTC->MODE0.INTENSET.bit.CMP0 = 1;
		while (RTC->MODE0.STATUS.bit.SYNCBUSY);
		
		NVIC_SetPriority(RTC_IRQn, 0);
		NVIC_EnableIRQ(RTC_IRQn);
	}
	else
	{
		NVIC_DisableIRQ(RTC_IRQn);
	}
	
	RTC->MODE0.CTRL.bit.ENABLE = 1;
	while (RTC->MODE0.STATUS.bit.SYNCBUSY);
	
	RTC->MODE0.READREQ.reg = RTC_READREQ_RREQ | RTC_READREQ_RCONT | 0x0010;
	while (RTC->MODE0.STATUS.bit.SYNCBUSY);
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

