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
//-------------------------------- USART --------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "USART.h"


#ifndef USART_UCPHA_bm
#define USART_UCPHA_bm   0x02
#endif // USART_UCPHA_bm

#ifndef USART_DORD_bm
#define USART_DORD_bm   0x04
#endif // USART_DORD_bm


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Create(USART_t* pUart, uint32_t sys_speed, uint32_t boud, XUSART_PIN_CFG pCfg)
{
	if (pUart != 0)
	{
		pUart->CTRLA = 0;
		pUart->CTRLB = 0;
		pUart->CTRLC = 0;
		pUart->STATUS = USART_RXCIF_bm|USART_TXCIF_bm;
		
		if (pCfg & DTX)
		{
			pUart->CTRLB |= USART_TXEN_bm; // Enable TX
		}
		
		if (pCfg & DRX)
		{
			pUart->CTRLB  |= USART_RXEN_bm ; // Enable RX
		}
		
		boud = sys_speed / boud;
		
		if (pCfg & SPI_CLK)
		{
			pUart->CTRLC = USART_CMODE_MSPI_gc;
			boud /= 2 ;
		}
		else
		{
			pUart->CTRLC = USART_CHSIZE_8BIT_gc;
			boud /= 16 ;
		}
		
		if (boud > 1)
		{
			boud--;
		}

		pUart->BAUDCTRLA = (uint8_t)boud ;
		pUart->BAUDCTRLB = ((uint8_t)(boud >> 8)) & 0x0f;
				
// 		uint8_t x = pUart->DATA ;
// 		x = pUart->DATA ;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Close(USART_t* pUart)
{
	if (pUart != 0)
	{
		pUart->CTRLA = 0;
		pUart->CTRLB = 0;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_interrupt_Cfg(USART_t* pUart, USART_RXCINTLVL_t irx, USART_TXCINTLVL_t itx, USART_DREINTLVL_t iempty)
{
	if (pUart != 0)
	{
		pUart->CTRLA = irx| itx| iempty;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_SPI_Config(USART_t* pUart, PORT_t* port, uint8_t clk_pin, uint8_t spi_mode, uint8_t lsb_first)
{
	if((pUart != 0) && (port != 0))
	{
		uint8_t cfg_c = USART_CMODE_MSPI_gc;
		
		if ((spi_mode == 1)||(spi_mode > 2))
		{
			cfg_c |= USART_UCPHA_bm;
		}
		
		if (lsb_first)
		{
			cfg_c |= USART_DORD_bm;
		}
		
		pUart->CTRLC = cfg_c;
		
		port->OUTSET = clk_pin;
		port->DIRSET = clk_pin;
		PORTCFG_MPCMASK =  clk_pin;
		if (spi_mode > 1)
		{
			port->PIN0CTRL = PORT_INVEN_bm;
		}
		else
		{
			port->PIN0CTRL = 0;
		}
	}
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t Usart_SPI_Transfer(USART_t* pUart, uint8_t c)
{
	while((pUart->STATUS & USART_DREIF_bm) == 0);	
	pUart->DATA = c;	
	while((pUart->STATUS & USART_TXCIF_bm) == 0);	
	pUart->STATUS |= USART_TXCIF_bm;
	
	return (pUart->DATA);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Send(USART_t* pUart ,uint8_t c)
{
	while((pUart->STATUS & USART_DREIF_bm) == 0);
	pUart->DATA = c;
}

uint8_t Usart_Get(USART_t* pUart)
{
	while ((pUart->STATUS & USART_RXCIF_bm) == 0);
	return pUart->DATA;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Usart_Print(USART_t* pUart ,char *s)
{
	while (*s != 0)
	{
		while((pUart->STATUS & USART_DREIF_bm) == 0);
		pUart->DATA = *s;
		s++;
	}
}

void Usart_Print_P(USART_t* pUart ,const char *s)
{
	char ch ;
	while(1)
	{
		ch = pgm_read_byte(s) ;
		if (ch == 0)
		{
			break;
		} 
		
		while((pUart->STATUS & USART_DREIF_bm) == 0);
		pUart->DATA = ch; 
		s++;
	}
}



//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
