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
//-------------------------------- Clock --------------------------------//
//#######################################################################//
#include "sam.h"
#include "Clock.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Clock_Generator_Disable(uint8_t id)
{
	if (id != 0)
	{
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(id);
		
		while (GCLK->STATUS.bit.SYNCBUSY);
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Clock_Generator_Set(uint8_t id, GENERATOR_SOURCE src, uint16_t divFactor)
{
	GCLK_GENCTRL_Type x;
	
	x.reg = GCLK_GENCTRL_ID(id) | GCLK_GENCTRL_SRC(src) | GCLK_GENCTRL_GENEN;
	
	if (divFactor & 0x0001)
	{
		x.reg |= GCLK_GENCTRL_IDC;
	}
	
	GCLK->GENDIV.reg = GCLK_GENDIV_ID(id) | GCLK_GENDIV_DIV(divFactor);
	
	while (GCLK->STATUS.bit.SYNCBUSY);
	
	GCLK->GENCTRL.reg = x.reg;
	
	while (GCLK->STATUS.bit.SYNCBUSY);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Clock_Multiplexer_Set(uint8_t id, uint8_t gen)
{
	GCLK_CLKCTRL_Type x;
		
	while (GCLK->STATUS.bit.SYNCBUSY);
	
	x.reg = GCLK_CLKCTRL_ID(id);
	
	GCLK->CLKCTRL.reg = x.reg;
	
	while(GCLK->CLKCTRL.bit.CLKEN != 0);
	
	x.reg |= GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(gen);
	
	GCLK->CLKCTRL.reg = x.reg;
	
	while (GCLK->STATUS.bit.SYNCBUSY);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Clock_Multiplexer_Disable(uint8_t id)
{
	while (GCLK->STATUS.bit.SYNCBUSY);
	
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(id);
	
	while (GCLK->STATUS.bit.SYNCBUSY);
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_XTAL_Enable(uint32_t frequency)
{
	frequency /= 1000000;
	if (frequency > 16)
	{
		frequency = 0x04;
	}
	else if (frequency > 8)
	{
		frequency = 0x03;
	}
	else if (frequency > 4)
	{
		frequency = 0x02;
	}
	else if (frequency > 2)
	{
		frequency = 0x01;
	}
	else
	{
		frequency = 0;
	}
	
	SYSCTRL->XOSC.reg = SYSCTRL_XOSC_GAIN(frequency)
	| SYSCTRL_XOSC_XTALEN
	| SYSCTRL_XOSC_STARTUP(0x3)
	| SYSCTRL_XOSC_ENABLE;
	
	while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_XOSCRDY) == 0);
}

void OSC_XTAL_Disable()
{
	SYSCTRL->XOSC.bit.ENABLE = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_XTAL_32k_Enable()
{
	SYSCTRL->XOSC32K.reg = SYSCTRL_XOSC32K_EN32K
	| SYSCTRL_XOSC32K_XTALEN
	| SYSCTRL_XOSC32K_STARTUP(0x3)
	| SYSCTRL_XOSC32K_ENABLE;
	
	while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_XOSC32KRDY) == 0);
}

void OSC_XTAL_32k_Disable()
{
	SYSCTRL->XOSC32K.bit.ENABLE = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_RC32k_Enable()
{
	uint32_t calib = (*((uint32_t *) FUSES_OSC32KCAL_ADDR) & FUSES_OSC32KCAL_Msk) >> FUSES_OSC32KCAL_Pos;
	SYSCTRL->OSC32K.reg =  SYSCTRL_OSC32K_CALIB(calib)
	| SYSCTRL_OSC32K_STARTUP(0x3)
	| SYSCTRL_OSC32K_EN32K
	| SYSCTRL_OSC32K_ENABLE;
	
	while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_OSC32KRDY) == 0);
}

void OSC_RC32k_Disable()
{
	SYSCTRL->OSC32K.bit.ENABLE = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_RC8M_Enable(uint8_t prescaler)
{
	SYSCTRL->OSC8M.bit.PRESC = prescaler & 0x03;
	SYSCTRL->OSC8M.bit.ONDEMAND = 0;
	SYSCTRL->OSC8M.bit.RUNSTDBY = 0;
	SYSCTRL->OSC8M.bit.ENABLE = 1;
	
	while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_OSC8MRDY) == 0);
}

void OSC_RC8M_Disable()
{
	SYSCTRL->OSC8M.bit.ENABLE = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_DFLL_Enable(uint8_t gen, uint16_t mulFactor)
{
	/* 1 wait state required @ 3.3V & 48MHz */
	NVMCTRL->CTRLB.bit.RWS = NVMCTRL_CTRLB_RWS_HALF_Val;
		
	Clock_Multiplexer_Set(GCLK_CLKCTRL_ID_DFLL48M_Val, gen);
	
	/* Clear the lock flags */
	SYSCTRL->INTFLAG.reg |= SYSCTRL_INTFLAG_DFLLLCKF | 
							SYSCTRL_INTFLAG_DFLLLCKC | 
							SYSCTRL_INTFLAG_DFLLRDY;
							
	/* Enable the DFLL48M in open loop mode */
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	SYSCTRL->DFLLCTRL.reg = (uint16_t)(SYSCTRL_DFLLCTRL_QLDIS | SYSCTRL_DFLLCTRL_CCDIS | SYSCTRL_DFLLCTRL_ENABLE);
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	/* Set up the Multiplier, Coarse and Fine steps */
	SYSCTRL_DFLLMUL_Type dfllmul = {
		.bit.CSTEP = 31,
		.bit.FSTEP = 511,
		.bit.MUL = mulFactor
	};
	
	SYSCTRL->DFLLMUL.reg = dfllmul.reg;
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	/* load factory calibrated values */
	uint32_t tmpCalib = *(uint32_t*)FUSES_DFLL48M_COARSE_CAL_ADDR;
	tmpCalib &= FUSES_DFLL48M_COARSE_CAL_Msk;
	tmpCalib >>= FUSES_DFLL48M_COARSE_CAL_Pos;
		
	SYSCTRL->DFLLVAL.bit.COARSE = tmpCalib;
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	/* Switch DFLL48M to Closed Loop mode and enable WAITLOCK */
	SYSCTRL->DFLLCTRL.reg |= (SYSCTRL_DFLLCTRL_MODE);
	while (!SYSCTRL->PCLKSR.bit.DFLLRDY);
		
	/* Wait for fine and coarse lock */
	while (!SYSCTRL->INTFLAG.bit.DFLLLCKC && !SYSCTRL->INTFLAG.bit.DFLLLCKF);
	
	/* Wait for the DFLL to be ready */
	while (!SYSCTRL->INTFLAG.bit.DFLLRDY);
}

void OSC_DFLL_Disable()
{
	SYSCTRL->DFLLCTRL.bit.ENABLE = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void _Set_Bus_Dividers(uint8_t cpuDiv, uint8_t APBxDIV)
{
	while (!PM->INTFLAG.bit.CKRDY);
	
	PM->CPUSEL.reg  = PM_CPUSEL_CPUDIV(cpuDiv);
	PM->APBASEL.reg = PM_APBASEL_APBADIV(APBxDIV);
	PM->APBBSEL.reg = PM_APBBSEL_APBBDIV(APBxDIV);
	PM->APBCSEL.reg = PM_APBCSEL_APBCDIV(APBxDIV);
}


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

