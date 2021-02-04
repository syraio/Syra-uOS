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

void DMA_Enable();

void DMA_Disable();

void DMA_Reset_Channel(uint8_t ch);

uint8_t DMA_isBusy(uint8_t ch);

DMA_CH_t* DMA_Get_CH(uint8_t ch);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DMA_m2m(uint8_t ch, uint8_t* m_in, uint8_t* m_out , uint16_t sz);

void DMA_mem_Reg16(uint8_t ch, uint16_t* m, uint16_t* rg, uint16_t sz, DMA_CH_TRIGSRC_t trgr);
void DMA_Reg16_mem(uint8_t ch, uint16_t* rg, uint16_t* m, uint16_t sz, DMA_CH_TRIGSRC_t trgr);

void DMA_mem_Reg(uint8_t ch, uint8_t* m, uint8_t* rg, uint16_t sz, DMA_CH_TRIGSRC_t trgr);
void DMA_Reg_mem(uint8_t ch, uint8_t* rg, uint8_t* m, uint16_t sz, DMA_CH_TRIGSRC_t trgr);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////







