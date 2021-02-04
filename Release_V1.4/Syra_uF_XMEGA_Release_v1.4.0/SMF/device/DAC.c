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
//---------------------------- DAC Driver -------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <stddef.h>
#include <avr/pgmspace.h>

#include "NVM.h"
#include "DAC.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DACB_Setup(DAC_CHSEL_t ch_Operation)
{
	PR_PRPB &= ~(PR_DAC_bm);
	
	DACB_CH0OFFSETCAL = Get_Calibration( offsetof(NVM_PROD_SIGNATURES_t, DACB0OFFCAL) );
	DACB_CH0GAINCAL = Get_Calibration( offsetof(NVM_PROD_SIGNATURES_t, DACB0GAINCAL) );
	
	DACB_CH1OFFSETCAL = Get_Calibration( offsetof(NVM_PROD_SIGNATURES_t, DACB1OFFCAL) );
	DACB_CH1GAINCAL = Get_Calibration( offsetof(NVM_PROD_SIGNATURES_t, DACB1GAINCAL) );
		
	DACB_CTRLB = ch_Operation;
	
	DACB_CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;	
}

void DACB_Disable()
{	
	DACB_CTRLB = 0;
	
	DACB_CTRLA = 0;
	
	PR_PRPB |= PR_DAC_bm;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void DACB_Write_CH0(uint16_t data)
{
	if (DACB_STATUS & DAC_CH0DRE_bm)
	{
		DACB_CH1DATA = data;
	}
}

void DACB_Write_CH1(uint16_t data)
{
	if (DACB_STATUS & DAC_CH1DRE_bm)
	{
		DACB_CH1DATA = data;
	}
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
