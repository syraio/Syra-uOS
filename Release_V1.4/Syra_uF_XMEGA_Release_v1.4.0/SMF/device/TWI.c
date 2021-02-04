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
//--------------------------- TWI Driver --------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "GPIO.h"
#include "TWI.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TWI_Master_Create(TWI_t *pTwi, int32_t sys_speed, int32_t baud)
{
	if (pTwi != 0)
	{
		pTwi->CTRL = 0;
		pTwi->MASTER.CTRLA = 0;
		pTwi->MASTER.CTRLB = 0;
		pTwi->MASTER.CTRLC = 0;
		
		int32_t x = baud * 2 ;
		baud = sys_speed / x ;
		x = baud - 5 ;
		pTwi->MASTER.BAUD = x ;
		
		pTwi->MASTER.CTRLA = TWI_MASTER_ENABLE_bm;
		
		pTwi->MASTER.STATUS = TWI_MASTER_RIF_bm	|TWI_MASTER_WIF_bm
								|TWI_MASTER_ARBLOST_bm	|TWI_MASTER_BUSERR_bm;
		pTwi->MASTER.STATUS |= TWI_MASTER_BUSSTATE_IDLE_gc;
	}	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TWI_Master_Config(TWI_t *pTwi, uint8_t int_cfg)
{
	if (pTwi != 0)
	{
		pTwi->MASTER.CTRLA = int_cfg | TWI_MASTER_ENABLE_bm;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TWI_Master_Disable(TWI_t *pTwi)
{
	if (pTwi != 0)
	{
		pTwi->CTRL = 0;
		pTwi->MASTER.CTRLA = 0;
		pTwi->MASTER.CTRLB = 0;
		pTwi->MASTER.CTRLC = 0;		
	}	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t TWI_Start(TWI_t *pTwi, uint8_t devAddr)
{
	if (pTwi != 0)
	{
		devAddr <<= 1;
		pTwi->MASTER.ADDR = devAddr ;
		while(!(pTwi->MASTER.STATUS & TWI_MASTER_WIF_bm));
		
		if (pTwi->MASTER.STATUS & TWI_MASTER_RXACK_bm)
		{
			pTwi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
			return 0;
		}
		
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void  TWI_Stop(TWI_t *pTwi, uint8_t ack)
{
	if (pTwi != 0)
	{
		if(ack)
		{
			pTwi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
		}
		else
		{
			pTwi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
		}		
	}	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t TWI_Send(TWI_t *pTwi, uint8_t data)
{
	if (pTwi != 0)
	{
		pTwi->MASTER.DATA = data;
		while(!(pTwi->MASTER.STATUS&TWI_MASTER_WIF_bm));
		
		if (pTwi->MASTER.STATUS & TWI_MASTER_RXACK_bm)
		{
			pTwi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
			return 0;
		}
		
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t TWI_Get(TWI_t *pTwi)
{
	uint8_t data = 0;
	if (pTwi != 0)
	{
		while(!(pTwi->MASTER.STATUS&TWI_MASTER_RIF_bm));
		data = pTwi->MASTER.DATA;		
	}

	return data;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t TWI_Write(TWI_t *pTwi, uint8_t devAddr, uint8_t *data, uint8_t sz)
{
	if (pTwi != 0)
	{
		devAddr <<= 1;
		pTwi->MASTER.ADDR = devAddr;
		while(!(pTwi->MASTER.STATUS & TWI_MASTER_WIF_bm));
		
		if (pTwi->MASTER.STATUS & TWI_MASTER_RXACK_bm)
		{
			pTwi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
			return 0;
		}
		
		while(sz > 0)
		{
			pTwi->MASTER.DATA = *data;
			data++;
			while(!(pTwi->MASTER.STATUS&TWI_MASTER_WIF_bm));
			if (pTwi->MASTER.STATUS & TWI_MASTER_RXACK_bm)
			{
				pTwi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
				return 0;
			}
			
			sz--;
		}
		
		pTwi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
		
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t TWI_Read(TWI_t *pTwi, uint8_t devAddr, uint8_t* data, uint8_t sz)
{
	if (pTwi != 0)
	{
		devAddr <<= 1;
		pTwi->MASTER.ADDR = devAddr | 0x01;
		while(!(pTwi->MASTER.STATUS & TWI_MASTER_RIF_bm));
		
		while(sz > 0)
		{
			sz--;
			*data = pTwi->MASTER.DATA;
			data++;
			
			if (sz > 0)
			{
				pTwi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
				while(!(pTwi->MASTER.STATUS&TWI_MASTER_RIF_bm));
			}
		}
		
		pTwi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm |TWI_MASTER_CMD_STOP_gc;
		
		return 1;
	}
	
	return 0;
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////





