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
//--------------------------  DMA Controller  ---------------------------//
//#######################################################################//
#include <avr/io.h>

#include "DMA.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_Enable()
{
	PR_PRGEN &= ~(PR_DMA_bm);
	DMA_CTRL = DMA_ENABLE_bm;    // Enable, single buffer, round robin
}

void DMA_Disable()
{
	do{}while(DMA_STATUS != 0);
	DMA_CTRL = 0;    // Disable
	PR_PRGEN |= PR_DMA_bm;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_Reset_Channel(uint8_t ch)
{
	DMA_CH_t* pCH = DMA_Get_CH(ch);
	
	pCH->CTRLA = 0 ;  // Disable
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t DMA_isBusy(uint8_t ch)
{
	uint8_t flg = 0;
	
	if (ch == 0)
	{
		flg = DMA_CH0BUSY_bm;
	}
	else if (ch == 1)
	{
		flg = DMA_CH1BUSY_bm;
	}
	else if (ch == 2)
	{
		flg = DMA_CH2BUSY_bm;
	}
	else if (ch == 3)
	{
		flg = DMA_CH3BUSY_bm;
	}
	else
	{
		return 0;
	}
	
	if (DMA_STATUS & flg)
	{
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
DMA_CH_t* DMA_Get_CH(uint8_t ch)
{
	DMA_CH_t* pCH = 0;
	
	if (ch == 0)
	{
		pCH = &DMA.CH0;
		DMA_INTFLAGS |= DMA_CH0TRNIF_bm;
	}
	else if (ch == 1)
	{
		pCH = &DMA.CH1;
		DMA_INTFLAGS |= DMA_CH1TRNIF_bm;
	}
	else if (ch == 2)
	{
		pCH = &DMA.CH2;
		DMA_INTFLAGS |= DMA_CH2TRNIF_bm;
	}
	else if (ch == 3)
	{
		pCH = &DMA.CH3;
		DMA_INTFLAGS |=DMA_CH3TRNIF_bm;
	}
	
	return pCH;	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_m2m(uint8_t ch, uint8_t* m_in, uint8_t* m_out , uint16_t sz)
{
	DMA_CH_t* pCH = DMA_Get_CH(ch);
		
	pCH->CTRLA = DMA_CH_BURSTLEN_1BYTE_gc;  // 1 byte, burst
	pCH->ADDRCTRL = DMA_CH_SRCDIR_INC_gc |  DMA_CH_DESTDIR_INC_gc ;
	pCH->TRIGSRC= DMA_CH_TRIGSRC_OFF_gc;  // trigger source
	pCH->TRFCNT = (uint16_t)sz;   // Buffer size
	pCH->SRCADDR0 =((uint16_t)(m_in))&0xFF;
	pCH->SRCADDR1 =(((uint16_t)(m_in))>>8)&0xFF;
	pCH->SRCADDR2 = 0;
	pCH->DESTADDR0  =((uint16_t)(m_out))&0xFF;
	pCH->DESTADDR1  =(((uint16_t)(m_out))>>8)&0xFF;
	pCH->DESTADDR2  = 0;
	pCH->CTRLA |= DMA_CH_ENABLE_bm | DMA_CH_TRFREQ_bm ;  // Enable	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_mem_Reg(uint8_t ch, uint8_t* m, uint8_t* rg, uint16_t sz, DMA_CH_TRIGSRC_t trgr)
{
	DMA_CH_t* pCH = DMA_Get_CH(ch);
		
	pCH->CTRLA =  DMA_CH_SINGLE_bm |DMA_CH_BURSTLEN_1BYTE_gc;  // 1 byte, burst
	pCH->ADDRCTRL =	DMA_CH_SRCRELOAD_BLOCK_gc | DMA_CH_SRCDIR_INC_gc ;
	pCH->ADDRCTRL |= DMA_CH_DESTRELOAD_BURST_gc ;
	pCH->TRIGSRC = trgr;  // trigger source
	pCH->TRFCNT = sz;   // Buffer size
	pCH->SRCADDR0 =((uint16_t)(m))&0xFF;
	pCH->SRCADDR1 =(((uint16_t)(m))>>8)&0xFF;
	pCH->SRCADDR2 = 0;
	pCH->DESTADDR0 =((uint16_t)(rg))&0xFF;
	pCH->DESTADDR1 =(((uint16_t)(rg))>>8)&0xFF;
	pCH->DESTADDR2 = 0;
	pCH->CTRLA |= DMA_CH_ENABLE_bm;  // Enable
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_Reg_mem(uint8_t ch, uint8_t* rg, uint8_t* m, uint16_t sz, DMA_CH_TRIGSRC_t trgr)
{
	DMA_CH_t* pCH = DMA_Get_CH(ch);
	
	pCH->CTRLA = DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_1BYTE_gc;  // 1 byte, burst
	pCH->ADDRCTRL =	DMA_CH_SRCRELOAD_BURST_gc ;
	pCH->ADDRCTRL |= DMA_CH_DESTRELOAD_BLOCK_gc | DMA_CH_DESTDIR_INC_gc ;
	pCH->TRIGSRC = trgr;  // trigger source
	pCH->TRFCNT = sz;   // Buffer size
	pCH->SRCADDR0 =((uint16_t)(rg))&0xFF;
	pCH->SRCADDR1 =(((uint16_t)(rg))>>8)&0xFF;
	pCH->SRCADDR2 = 0;
	pCH->DESTADDR0  =((uint16_t)(m))&0xFF;
	pCH->DESTADDR1  =(((uint16_t)(m))>>8)&0xFF;
	pCH->DESTADDR2  = 0;
	pCH->CTRLA |= DMA_CH_ENABLE_bm ;  // Enable
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_mem_Reg16(uint8_t ch, uint16_t* m, uint16_t* rg, uint16_t sz, DMA_CH_TRIGSRC_t trgr)
{
	DMA_CH_t* pCH = DMA_Get_CH(ch);
	
	pCH->CTRLA = DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_2BYTE_gc;  // 2 byte, burst
	pCH->ADDRCTRL = DMA_CH_SRCRELOAD_BLOCK_gc | DMA_CH_SRCDIR_INC_gc ;
	pCH->ADDRCTRL |= DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_INC_gc ;
	pCH->TRIGSRC = trgr;  // trigger source
	pCH->TRFCNT = sz * 2;   // Buffer size
	pCH->SRCADDR0 =((uint16_t)(m))&0xFF;
	pCH->SRCADDR1 =(((uint16_t)(m))>>8)&0xFF;
	pCH->SRCADDR2 = 0;
	pCH->DESTADDR0  =((uint16_t)(rg))&0xFF;
	pCH->DESTADDR1  =(((uint16_t)(rg))>>8)&0xFF;
	pCH->DESTADDR2  = 0;
	pCH->CTRLA |= DMA_CH_ENABLE_bm;  // Enable
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_Reg16_mem(uint8_t ch, uint16_t* rg, uint16_t* m, uint16_t sz, DMA_CH_TRIGSRC_t trgr)
{
	DMA_CH_t* pCH = DMA_Get_CH(ch);
	
	pCH->CTRLA = DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_2BYTE_gc;  // 2 byte, burst
	pCH->ADDRCTRL = DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc ;
	pCH->ADDRCTRL |= DMA_CH_DESTRELOAD_BLOCK_gc | DMA_CH_DESTDIR_INC_gc ;
	pCH->TRIGSRC = trgr;  // trigger source
	pCH->TRFCNT = sz * 2;   // Buffer size
	pCH->SRCADDR0 =((uint16_t)(rg))&0xFF;
	pCH->SRCADDR1 =(((uint16_t)(rg))>>8)&0xFF;
	pCH->SRCADDR2 = 0;
	pCH->DESTADDR0  =((uint16_t)(m))&0xFF;
	pCH->DESTADDR1  =(((uint16_t)(m))>>8)&0xFF;
	pCH->DESTADDR2  = 0;
	pCH->CTRLA |= DMA_CH_ENABLE_bm ;  // Enable
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////



