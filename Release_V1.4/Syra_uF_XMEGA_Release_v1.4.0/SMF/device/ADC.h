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
 
 volatile uint8_t _ADCA_Busy;
 
///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void ADCA_Setup(ADC_PRESCALER_t pscl, ADC_REFSEL_t vref, ADC_RESOLUTION_t res);
void ADCA_EventSystem(ADC_EVACT_t evnt);
void ADCA_Disable();

void ADCA_CH_Config(uint8_t ch, ADC_CH_GAIN_t gain, ADC_CH_INPUTMODE_t in_mode ,ADC_CH_INTLVL_t int_lvl);
void ADCA_CH_Mux(uint8_t ch, uint8_t pos, ADC_CH_MUXNEG_t nig);

uint16_t ADCA_Fix_12Bit(uint16_t v);
uint16_t ADCA_Fix_8Bit(uint16_t v);

int16_t ADCA_ReadCH0();
int16_t ADCA_ReadCH1();
int16_t ADCA_ReadCH2();
int16_t ADCA_ReadCH3();

int16_t ADCA_ReadCH0_Ex(uint8_t x);
int16_t ADCA_ReadCH1_Ex(uint8_t x);
int16_t ADCA_ReadCH2_Ex(uint8_t x);
int16_t ADCA_ReadCH3_Ex(uint8_t x);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////






