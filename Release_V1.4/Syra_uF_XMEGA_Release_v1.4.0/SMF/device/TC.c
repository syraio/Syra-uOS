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
//--------------------------  Timer / Counter ---------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>

#include "TC.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TC_Get_Config(uint32_t sys_speed, uint32_t f, TIMER_CONFIG_t* cfg)
{
	if ((f == 0)||(cfg == 0))
	{
		return ;
	}
	
	uint32_t temp = (sys_speed / f);
	
	uint8_t x = TC_CLKSEL_OFF_gc;
	
	if (temp > 0xFFFD)
	{
		temp >>= 1;
		if (temp > 0xFFFD)
		{
			temp >>= 1;
			if (temp > 0xFFFD)
			{
				temp >>= 1;
				if (temp > 0xFFFD)
				{
					temp >>= 3;
					if (temp > 0xFFFD)
					{
						temp >>= 2;
						if (temp > 0xFFFD)
						{
							temp >>= 2;
							if (temp < 0xFFFE)
							{
								x = TC_CLKSEL_DIV1024_gc;
							}
						}
						else
						{
							x = TC_CLKSEL_DIV256_gc;
						}
					}
					else
					{
						x = TC_CLKSEL_DIV64_gc;
					}
				}
				else
				{
					x = TC_CLKSEL_DIV8_gc;
				}
			}
			else
			{
				x = TC_CLKSEL_DIV4_gc;
			}
		}
		else
		{
			x = TC_CLKSEL_DIV2_gc;
		}
	}
	else
	{
		x = TC_CLKSEL_DIV1_gc;
	}
	
	cfg->per = temp;
	cfg->src = x;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TC_Stop(HTIMER tc)
{	
	if (tc != 0)
	{
		tc->CTRLA = 0;
		tc->CTRLB = 0 ;
		tc->CTRLC = 0 ;
		tc->CTRLD = 0 ;
		tc->CTRLE = 0 ;
		
		tc->INTCTRLA = 0;
		tc->INTCTRLB = 0;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TC_Normal_Start(HTIMER tc, TIMER_CONFIG_t* cfg, TC_OVFINTLVL_t ovf)
{
	if ((tc == 0)||(cfg == 0))
	{
		return;
	}
		
	if (cfg->src == 0)
	{
		return;
	}
	
	tc->CTRLA = 0;
	tc->CTRLB = TC_WGMODE_NORMAL_gc;
	tc->CTRLC = 0;
	tc->CTRLD = 0;
	tc->CTRLE = 0;
	tc->INTCTRLA = 0;
	tc->INTCTRLB = 0;
	
	tc->CNT = 0;
	
	tc->PER = cfg->per;
	
	tc->INTCTRLA = ovf;
	
	tc->CTRLA = cfg->src;	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TC_PWM_Start(HTIMER tc, TIMER_CONFIG_t* cfg, TC_COMP_REG_t cmpReg, uint16_t w)
{
	if ((tc == 0)||(cfg == 0))
	{
		return;
	}
		
	if (cfg->src == 0)
	{
		return;
	}
	
	uint32_t comp_val = 0;
	
	tc->CTRLA = 0;
	
	tc->CTRLB &= ~(TC0_WGMODE_gm);
	tc->CTRLB |= TC_WGMODE_SS_gc;
	
	tc->CNT = 0;
	
	tc->PER = cfg->per;
	
	if (w > 995)
	{
		comp_val = cfg->per;
	}
	else
	{
		comp_val = w;
		comp_val *= cfg->per;
		comp_val /= 1000 ;
	}
	
	if (cmpReg & TC_CMP_A)
	{
		tc->CCA =  comp_val;
		tc->CTRLB |= TC0_CCAEN_bm;
		tc->CTRLC |= TC0_CMPA_bm ;
	}
	
	if (cmpReg & TC_CMP_B)
	{
		tc->CCB =  comp_val;
		tc->CTRLB |= TC0_CCBEN_bm;
		tc->CTRLC |= TC0_CMPB_bm ;
	}
	
	if (cmpReg & TC_CMP_C)
	{
		tc->CCC =  comp_val;
		tc->CTRLB |= TC0_CCCEN_bm;
		tc->CTRLC |= TC0_CMPC_bm ;
	}
	
	if (cmpReg & TC_CMP_D)
	{
		tc->CCD =  comp_val;
		tc->CTRLB |= TC0_CCDEN_bm;
		tc->CTRLC |= TC0_CMPD_bm ;
	}
	
	tc->CTRLA = cfg->src;	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TC_PWM_Update(HTIMER tc, TC_COMP_REG_t cmpReg, uint16_t w)
{	
	if (tc != 0)
	{
		uint32_t comp_val = 0;
		uint32_t per_val  =	tc->PER;
		
		if (w > 995)
		{
			comp_val = per_val;
		}
		else
		{
			comp_val = w;
			comp_val *= per_val;
			comp_val /= 1000 ;
		}
		
		if (cmpReg & TC_CMP_A)
		{
			tc->CCA =  comp_val;
		}
		
		if (cmpReg & TC_CMP_B)
		{
			tc->CCB =  comp_val;
		}
		
		if (cmpReg & TC_CMP_C)
		{
			tc->CCC =  comp_val;
		}
		
		if (cmpReg & TC_CMP_D)
		{
			tc->CCD =  comp_val;
		}	
	}		
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void TC_PWM_Disable(HTIMER tc, TC_COMP_REG_t cmpReg)
{
	if (tc != 0)
	{
		if (cmpReg & TC_CMP_A)
		{
			tc->CCA =  0;
			tc->CTRLB &= ~(TC0_CCAEN_bm);
			tc->CTRLC &= ~( TC0_CMPA_bm);
		}
		
		if (cmpReg & TC_CMP_B)
		{
			tc->CCB =  0;
			tc->CTRLB &= ~( TC0_CCBEN_bm);
			tc->CTRLC &= ~( TC0_CMPB_bm);
		}
		
		if (cmpReg & TC_CMP_C)
		{
			tc->CCC =  0;
			tc->CTRLB &= ~( TC0_CCCEN_bm);
			tc->CTRLC &= ~( TC0_CMPC_bm);
		}
		
		if (cmpReg & TC_CMP_D)
		{
			tc->CCD =  0;
			tc->CTRLB &= ~( TC0_CCDEN_bm);
			tc->CTRLC &= ~( TC0_CMPD_bm);
		}
	}	
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

