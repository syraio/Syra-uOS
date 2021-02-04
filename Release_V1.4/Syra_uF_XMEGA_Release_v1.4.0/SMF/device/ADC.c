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
//---------------------------- ADC Driver -------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <stddef.h>
#include <avr/pgmspace.h>

#include "NVM.h"
#include "ADC.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void ADCA_Setup(ADC_PRESCALER_t pscl, ADC_REFSEL_t vref, ADC_RESOLUTION_t res) 
{
	PR_PRPA &= ~(PR_ADC_bm);
	
	ADCA_CTRLA = 0;
	
	ADCA_CALL = Get_Calibration(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
	ADCA_CALH = Get_Calibration(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1)); 
	
	ADCA_PRESCALER = pscl;
	
	ADCA_EVCTRL = 0;
	
	if (vref == ADC_REFSEL_INT1V_gc)
	{
		vref |= ADC_BANDGAP_bm;
	}
	
	ADCA_REFCTRL = vref;
	
	ADCA_CTRLB = res | ADC_CURRLIMIT_MED_gc | ADC_CONMODE_bm;
	
	ADCA_INTFLAGS = ADC_CH0IF_bm |ADC_CH1IF_bm|ADC_CH2IF_bm|ADC_CH3IF_bm;
	
	_ADCA_Busy = 0;
	
	ADCA_CTRLA = ADC_ENABLE_bm;	
}

void ADCA_Disable()
{	
	ADCA_CTRLA = 0;
	PR_PRPA |= PR_ADC_bm;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void ADCA_EventSystem(ADC_EVACT_t evnt)
{
	//ADCA_EVCTRL = ADC_SWEEP_0_gc | ADC_EVSEL_0123_gc | ADC_EVACT_CH01_gc;	// event channel 0 triggers ADC channel 0
	ADCA_EVCTRL = evnt;	
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void ADCA_CH_Config(uint8_t ch, ADC_CH_GAIN_t gain, ADC_CH_INPUTMODE_t in_mode ,ADC_CH_INTLVL_t int_lvl)
{
	if (ch == 0)
	{
		ADCA_CH0_CTRL = gain | in_mode;
		ADCA_CH0_INTCTRL = int_lvl;
	}
	else if (ch == 1)
	{
		ADCA_CH1_CTRL = gain | in_mode;
		ADCA_CH1_INTCTRL = int_lvl;
	}
	else if (ch == 2)
	{
		ADCA_CH2_CTRL = gain | in_mode;
		ADCA_CH2_INTCTRL = int_lvl;
	}
	else if (ch == 3)
	{
		ADCA_CH3_CTRL = gain | in_mode;
		ADCA_CH3_INTCTRL = int_lvl;
	}
}

void ADCA_CH_Mux(uint8_t ch, uint8_t pos, ADC_CH_MUXNEG_t nig)
{
	pos <<= ADC_CH_MUXPOS_gp;
	pos &= ADC_CH_MUXPOS_gm;
	pos |= nig & ADC_CH_MUXNEG_gm;
	
	if (ch == 0)
	{
		ADCA_CH0_MUXCTRL = pos;
	}
	else if (ch == 1)
	{
		ADCA_CH1_MUXCTRL = pos;
	}
	else if (ch == 2)
	{
		ADCA_CH2_MUXCTRL = pos;
	}
	else if (ch == 3)
	{
		ADCA_CH3_MUXCTRL = pos;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint16_t ADCA_Fix_12Bit(uint16_t v)
{
	if (v > 214)
	{
		v -= 214;
	}
	else
	{
		v = 0;
	}
	
	if (v > 3700)
	{
		v = 3700;
	}
	
	return v;
}

uint16_t ADCA_Fix_8Bit(uint16_t v)
{
	if (v > 12)
	{
		v -= 12;
	}
	else
	{
		v = 0;
	}
	
	if (v > 230)
	{
		v = 230;
	}
	
	return v;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
int16_t ADCA_ReadCH0()
{
	int16_t res = 0;
	_ADCA_Busy = 1;
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH0_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH0_INTFLAGS == 0);
	ADCA_CH0_INTFLAGS = ADC_CH_CHIF_bm;
	
	res = ADCA_CH0RES ;
	_ADCA_Busy = 0;
	
	return res ;
}

int16_t ADCA_ReadCH1()
{
	_ADCA_Busy = 1;	
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH1_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH1_INTFLAGS == 0);
	ADCA_CH1_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH1RES ;	
	_ADCA_Busy = 0;
	
	return res ;
}


int16_t ADCA_ReadCH2()
{
	_ADCA_Busy = 1;
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH2_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH2_INTFLAGS == 0);
	ADCA_CH2_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH2RES ;
	_ADCA_Busy = 0;
	
	return res ;
}

int16_t ADCA_ReadCH3()
{
	_ADCA_Busy = 1;	
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH3_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH3_INTFLAGS == 0);
	ADCA_CH3_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH3RES;
	_ADCA_Busy = 0;
	
	return res;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
int16_t ADCA_ReadCH0_Ex(uint8_t x)
{
	_ADCA_Busy = 1;
	
	x <<= ADC_CH_MUXPOS_gp;
	x &= ADC_CH_MUXPOS_gm;
	x |= ADCA_CH0_MUXCTRL & ADC_CH_MUXNEG_gm;
	ADCA_CH0_MUXCTRL = x;
	
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH0_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH0_INTFLAGS == 0);
	ADCA_CH0_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH0RES;
	_ADCA_Busy = 0;
	
	return res;
}


int16_t ADCA_ReadCH1_Ex(uint8_t x)
{
	_ADCA_Busy = 1;
	
	x <<= ADC_CH_MUXPOS_gp;
	x &= ADC_CH_MUXPOS_gm;
	x |= ADCA_CH1_MUXCTRL & ADC_CH_MUXNEG_gm;
	ADCA_CH1_MUXCTRL = x;
		
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH1_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH1_INTFLAGS == 0);
	ADCA_CH1_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH1RES;
	_ADCA_Busy = 0;
	
	return res;
}


int16_t ADCA_ReadCH2_Ex(uint8_t x)
{
	_ADCA_Busy = 1;
	
	x <<= ADC_CH_MUXPOS_gp;
	x &= ADC_CH_MUXPOS_gm;
	x |= ADCA_CH2_MUXCTRL & ADC_CH_MUXNEG_gm;
	ADCA_CH2_MUXCTRL = x;
	
	ADCA_CTRLA |= ADC_FLUSH_bm ;
	
	ADCA_CH2_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH2_INTFLAGS == 0);
	ADCA_CH2_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH2RES;
	_ADCA_Busy = 0;
	
	return res;
}


int16_t ADCA_ReadCH3_Ex(uint8_t x)
{
	_ADCA_Busy = 1;
	
	x <<= ADC_CH_MUXPOS_gp;
	x &= ADC_CH_MUXPOS_gm;
	x |= ADCA_CH3_MUXCTRL & ADC_CH_MUXNEG_gm;
	ADCA_CH3_MUXCTRL = x;
	
	ADCA_CTRLA |= ADC_FLUSH_bm;
	
	ADCA_CH3_CTRL |= ADC_CH_START_bm;
	while (ADCA_CH3_INTFLAGS == 0);
	ADCA_CH3_INTFLAGS = ADC_CH_CHIF_bm;
	
	int16_t res = ADCA_CH3RES;
	_ADCA_Busy = 0;
	
	return res;
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////