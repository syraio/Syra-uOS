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
//---------------------------------- USART -------------------------------//
//#######################################################################//
#include "sam.h"
#include "USART.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Create(Sercom* pModule, uint16_t baudReg, uint8_t txPad, uint8_t rxPad)
{	
	pModule->USART.CTRLA.bit.ENABLE = 0;
	
	SERCOM_USART_CTRLA_Type ctrlA;
	ctrlA.reg = SERCOM_USART_CTRLA_MODE_USART_INT_CLK |
				SERCOM_USART_CTRLA_RUNSTDBY |
				SERCOM_USART_CTRLA_DORD|
				SERCOM_USART_CTRLA_ENABLE;
	
	ctrlA.bit.RXPO = rxPad;
	ctrlA.bit.TXPO = txPad;
	
	while(pModule->USART.STATUS.bit.SYNCBUSY);
	pModule->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | 
	SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0);
		
	while(pModule->USART.STATUS.bit.SYNCBUSY);
	pModule->USART.BAUD.reg = baudReg;
	
	while(pModule->USART.STATUS.bit.SYNCBUSY);
	pModule->USART.CTRLA.reg = ctrlA.reg;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Send(Sercom* pModule, char c)
{
	while (!(pModule->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE));
	while(pModule->USART.STATUS.bit.SYNCBUSY);
	pModule->USART.DATA.reg = c;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Print(Sercom* pModule, char *s)
{
	while (*s != 0)
	{
		while (!(pModule->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE));
		while(pModule->USART.STATUS.bit.SYNCBUSY);
		pModule->USART.DATA.reg = *s;
		s++;
	}
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

