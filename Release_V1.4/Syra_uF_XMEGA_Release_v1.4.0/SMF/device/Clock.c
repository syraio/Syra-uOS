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
//------------------------------ Clock ----------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <stddef.h>
#include <avr/cpufunc.h>

#include "NVM.h"
#include "Clock.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_RC32K_Enable()
{
	OSC_RC32KCAL = Get_Calibration(offsetof(NVM_PROD_SIGNATURES_t, RCOSC32K));
	OSC_CTRL |= OSC_RC32KEN_bm;
	while((OSC_STATUS & OSC_RC32KRDY_bm) == 0);
}

uint8_t OSC_RC32K_Disable()
{	
	if ((CLK_CTRL & CLK_SCLKSEL_gm) != CLK_SCLKSEL_RC32K_gc)
	{
		OSC_CTRL &= ~(OSC_RC32KEN_bm);
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_RC2M_Enable()
{
	OSC_CTRL |= OSC_RC2MEN_bm;
	while((OSC_STATUS & OSC_RC2MRDY_bm) == 0);
}

uint8_t OSC_RC2M_Disable()
{
	if ((CLK_CTRL & CLK_SCLKSEL_gm) != CLK_SCLKSEL_RC2M_gc)
	{
		OSC_CTRL &= ~(OSC_RC2MEN_bm);
		return 1;
	}	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_RC32M_Enable()
{
	OSC_CTRL |= OSC_RC32MEN_bm;
	while((OSC_STATUS & OSC_RC32MRDY_bm) == 0);
}

uint8_t OSC_RC32M_Disable()
{
	if ((CLK_CTRL & CLK_SCLKSEL_gm) != CLK_SCLKSEL_RC32M_gc)
	{
		OSC_CTRL &= ~(OSC_RC32MEN_bm);
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_XTAL_Enable(XOSC_TYPE xType)
{
	uint8_t x = OSC_XOSCSEL_XTAL_16KCLK_gc;
	
	if (xType == XOSC_XTAL_12TO16M)
	{
		x |= OSC_FRQRANGE_12TO16_gc;
	}
	else if (xType == XOSC_XTAL_9TO12M)
	{
		x |= OSC_FRQRANGE_9TO12_gc;
	}
	else if (xType == XOSC_XTAL_2TO9M)
	{
		x |= OSC_FRQRANGE_2TO9_gc;
	}
	else if (xType == XOSC_XTAL_04TO2M)
	{
		x |= OSC_FRQRANGE_04TO2_gc;
	}
	else if (xType == XOSC_XTAL_32k)
	{
		x = OSC_XOSCSEL_32KHz_gc;
	}
	else
	{
		x = OSC_XOSCSEL_EXTCLK_gc;
	}
		
	ccp_write_io((uint8_t *)&OSC_XOSCCTRL, x);
	
	OSC_CTRL |= OSC_XOSCEN_bm;
	while((OSC_STATUS & OSC_XOSCRDY_bm) == 0);
}

uint8_t OSC_XTAL_Disable()
{	
	if ((CLK_CTRL & CLK_SCLKSEL_gm) != CLK_SCLKSEL_XOSC_gc)
	{
		OSC_CTRL &= ~(OSC_XOSCEN_bm);
		return 1;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void OSC_PLL_Enable(OSC_PLLSRC_t clksrc, uint8_t pll_factor)
{	
	pll_factor &= OSC_PLLFAC_gm;
		
	if ((pll_factor < 32)&&(pll_factor > 1))
	{
		pll_factor |= clksrc;
				
		if (OSC_PLLCTRL != pll_factor)
		{
			OSC_PLLCTRL = pll_factor;
		}
		
		OSC_CTRL |= OSC_PLLEN_bm ;		
		while((OSC_STATUS & OSC_PLLRDY_bm) == 0);		
	}	
}

uint8_t OSC_PLL_Disable()
{	
	if ((CLK_CTRL & CLK_SCLKSEL_gm) != CLK_SCLKSEL_PLL_gc)
	{
		OSC_CTRL &= ~(OSC_PLLEN_bm);
		return 1;
	}
		
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
uint8_t Clock_Set(CLK_SCLKSEL_t clksrc)
{
	uint8_t rdy_mask;
	
	if (clksrc == CLK_SCLKSEL_XOSC_gc)
	{
		rdy_mask = OSC_XOSCRDY_bm;
	}
	else if (clksrc == CLK_SCLKSEL_RC32M_gc)
	{
		rdy_mask = OSC_RC32MRDY_bm;
	}
	else if (clksrc == CLK_SCLKSEL_RC32K_gc)
	{
		rdy_mask = OSC_RC32KRDY_bm;
	}
	else if (clksrc == CLK_SCLKSEL_PLL_gc)
	{
		rdy_mask = OSC_PLLRDY_bm;
	}
	else
	{
		rdy_mask = OSC_RC2MRDY_bm;
		clksrc = CLK_SCLKSEL_RC2M_gc;
	}
	
	if ((OSC_STATUS & rdy_mask) != 0)
	{		
		ccp_write_io((uint8_t*)&CLK_CTRL, clksrc);
		
		if ((CLK_CTRL & CLK_SCLKSEL_gm) == clksrc)
		{			
			return 1;
		}
	}
	
	return 0;
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

