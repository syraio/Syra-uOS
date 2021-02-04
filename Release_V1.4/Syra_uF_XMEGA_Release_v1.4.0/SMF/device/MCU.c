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
//------------------------------- MCU -----------------------------------//
//#######################################################################//
//------------------- Libraries
#include <avr/io.h>
#include <avr/cpufunc.h>

#include "MCU.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Power Reduction
void PR_Disable_All(uint8_t keepRTC)
{
	if (keepRTC)
	{
		PR_PRGEN = ~(PR_RTC_bm);
	}
	else
	{
		PR_PRGEN = 0xFF;
	}

	#ifdef PR_PRPA
	PR_PRPA = 0xFF;
	#endif // PR_PRPA

	#ifdef PR_PRPB
	PR_PRPB = 0xFF;
	#endif // PR_PRPB

	#ifdef PR_PRPC
	PR_PRPC = 0xFF;
	#endif // PR_PRPC

	#ifdef PR_PRPD
	PR_PRPD = 0xFF;
	#endif // PR_PRPD

	#ifdef PR_PRPE
	PR_PRPE = 0xFF;
	#endif // PR_PRPE

	#ifdef PR_PRPF
	PR_PRPF = 0xFF;
	#endif // PR_PRPF
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void Soft_Reset()
{	
	ccp_write_io((uint8_t *)&RST_CTRL, RST_SWRST_bm );
	
	while (1){}
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
