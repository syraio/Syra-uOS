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
typedef enum
{
	TC_CMP_A = 0x01,
	TC_CMP_B = 0x02,
	TC_CMP_C = 0x04,
	TC_CMP_D = 0x08
}TC_COMP_REG_t;

typedef struct
{
	uint16_t per;
	uint8_t src;	
}TIMER_CONFIG_t;


typedef TC0_t* HTIMER;

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- TC Functions

void TC_Get_Config(uint32_t sys_speed, uint32_t f, TIMER_CONFIG_t* cfg);

void TC_Normal_Start(HTIMER tc, TIMER_CONFIG_t* cfg, TC_OVFINTLVL_t ovf);
void TC_Stop(HTIMER tc);


void TC_PWM_Start(HTIMER tc, TIMER_CONFIG_t* cfg, TC_COMP_REG_t cmpReg, uint16_t w);
void TC_PWM_Update(HTIMER tc, TC_COMP_REG_t cmpReg, uint16_t w);
void TC_PWM_Disable(HTIMER tc, TC_COMP_REG_t cmpReg);


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
