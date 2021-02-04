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
//------------------------------  MCU -----------------------------------//
//#######################################################################//
//-------------------	Sleep Manager

#define  Set_Sleep_Mode_Idle()         set_sleep_mode(SLEEP_MODE_IDLE)

#define  Set_Sleep_Mode_PowerDown()    set_sleep_mode(SLEEP_MODE_PWR_DOWN)

#define  Set_Sleep_Mode_PowerSave()    set_sleep_mode(SLEEP_MODE_PWR_SAVE)


#define  Sleep_Now() {sleep_enable(); sleep_cpu(); sleep_disable();}
	

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------   Power Reduction

#define	PR_Enable(xPReg, xModule)	xPReg &= ~(xModule);

#define	PR_Disable(xPReg, xModule)	xPReg |= xModule;

void PR_Disable_All(uint8_t keepRTC);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------   PMIC & Interrupts
/*	Enable all interrupts in the PMIC.
	Enable the global interrupt flag.
*/
#define Interrupts_EnableALL(){\
	PMIC_CTRL |= PMIC_HILVLEN_bm |PMIC_MEDLVLEN_bm |PMIC_LOLVLEN_bm;\
	sei();\
}

/*	Disable all interrupts in the PMIC.
	Disable the global interrupt flag.
*/
#define Interrupts_DisableAll(){\
	PMIC_CTRL &= ~( PMIC_HILVLEN_bm |PMIC_MEDLVLEN_bm |PMIC_LOLVLEN_bm );\
	cli();\
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------   RST Controller
/**
 * \brief Chip-specific reset cause type capable of holding all chip reset
 * causes. Typically reflects the size of the reset cause register.
 */
typedef enum
{
//! \internal External reset cause
	RESET_CAUSE_EXTRST = RST_EXTRF_bm ,
//! \internal brown-out detected reset cause, same as for CPU
	RESET_CAUSE_BOD_IO = RST_BORF_bm,
//! \internal Brown-out detected reset cause, same as for I/O
	RESET_CAUSE_BOD_CPU = RST_BORF_bm,
//! \internal On-chip debug system reset cause
	RESET_CAUSE_OCD = RST_PDIRF_bm,
//! \internal Power-on-reset reset cause
	RESET_CAUSE_POR = RST_PORF_bm,
//! \internal Software reset reset cause
	RESET_CAUSE_SOFT = RST_SRF_bm,
//! \internal Spike detected reset cause
	RESET_CAUSE_SPIKE = RST_SDRF_bm,
//! \internal Watchdog timeout reset cause
	RESET_CAUSE_WDT = RST_WDRF_bm,
}RST_CAUSE_t;


#define Reset_get_causes()       ((RST_CAUSE_t)RST_STATUS)

#define Reset_clear_causes(x)    RST_STATUS = x

void Soft_Reset();

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////