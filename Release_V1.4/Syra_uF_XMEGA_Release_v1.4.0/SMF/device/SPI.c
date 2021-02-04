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
//-------------------------------- SPI ----------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "SPI.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void SPI_Master_Create(SPI_t* pSpi, PORT_t* port, SPI_PRESCALER_t Prclr)
{
	if (pSpi != 0)
	{
		if (port != 0)
		{
			port->DIRSET = PIN7_bm | PIN5_bm | PIN4_bm;
			port->OUTCLR = PIN7_bm | PIN5_bm;
			port->OUTSET = PIN4_bm;
			port->DIRCLR = PIN6_bm;
			
			PORTCFG_MPCMASK =  PIN7_bm | PIN6_bm| PIN5_bm | PIN4_bm;
			port->PIN0CTRL = 0;
		}
		
		pSpi->INTCTRL = SPI_INTLVL_OFF_gc ;
		
		pSpi->CTRL = SPI_MASTER_bm | SPI_MODE_0_gc | Prclr  ;
		
		pSpi->CTRL |= SPI_ENABLE_bm;
	}
}

void SPI_Close(SPI_t* pSpi, PORT_t* port)
{
	if (pSpi != 0)
	{
		pSpi->CTRL = 0;
		pSpi->INTCTRL = 0;
		
		if (port != 0)
		{
			port->OUTCLR = PIN7_bm | PIN6_bm| PIN5_bm | PIN4_bm;
			port->DIRCLR = PIN7_bm | PIN6_bm| PIN5_bm | PIN4_bm;
			
			PORTCFG_MPCMASK =  PIN7_bm | PIN6_bm| PIN5_bm | PIN4_bm;
			port->PIN0CTRL = PORT_OPC_PULLDOWN_gc;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void SPI_Config(SPI_t* pSpi, SPI_MODE_t md, SPI_INTLVL_t iLvl, uint8_t lsb)
{
	if (pSpi != 0)
	{
		pSpi->CTRL &= SPI_PRESCALER_gm | SPI_MASTER_bm | SPI_CLK2X_bm;
		
		pSpi->CTRL |= md ;
		
		if (lsb)
		{
			pSpi->CTRL |= SPI_DORD_bm;
		}
		
		pSpi->INTCTRL = iLvl ;
		
		pSpi->CTRL |= SPI_ENABLE_bm;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t SPI_Transfer(SPI_t* pSpi, uint8_t dat)
{
	uint8_t x = 0;
	if (pSpi != 0)
	{
		pSpi->DATA = dat ;
		while(!(pSpi->STATUS & SPI_IF_bm));
		x = pSpi->DATA ;
	}
		
	return x;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint16_t SPI_Print(SPI_t* pSpi, char* str)
{	
	uint16_t x = 0 ;
	if (pSpi != 0)
	{
		while(*str != 0)
		{
			pSpi->DATA = *str ;
			while(!(pSpi->STATUS & SPI_IF_bm));
			
			x++;
			str++;
		}
	}
	
	return x ;
}


uint16_t SPI_Print_P(SPI_t* pSpi, char* str)
{
	uint16_t x = 0 ;
	
	if (pSpi != 0)
	{
		char ch ;
		
		while(1)
		{
			ch = pgm_read_word(str);
			if (ch == 0)
			{
				break;
			}
			
			pSpi->DATA = ch ;
			while(!(pSpi->STATUS & SPI_IF_bm));
			
			x++;
			str++;
		}
	}
	
	return x ;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void SPI_Write(SPI_t* pSpi, uint8_t* dataOut, uint16_t sz)
{
	if (pSpi != 0)
	{
		while(sz > 0)
		{
			pSpi->DATA = *dataOut ;
			while(!(pSpi->STATUS & SPI_IF_bm));
			
			dataOut++;
			sz--;
		}
	}
}


void SPI_Write_P(SPI_t* pSpi, uint8_t* dataOut, uint16_t sz)
{
	if (pSpi != 0)
	{
		while(sz > 0)
		{
			pSpi->DATA = pgm_read_byte(dataOut) ;
			while(!(pSpi->STATUS & SPI_IF_bm));
			
			dataOut++;
			sz--;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void SPI_Read(SPI_t* pSpi, uint8_t dOut, uint8_t* dResp, uint16_t sz)
{
	if (pSpi != 0)
	{
		while(sz > 0)
		{
			pSpi->DATA = dOut ;
			while(!(pSpi->STATUS & SPI_IF_bm));
			
			if (dResp > 0)
			{
				*dResp = pSpi->DATA;
				dResp++;
			}
			sz--;
		}
	}
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

