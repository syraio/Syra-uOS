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
//-------------------------------- XMEGA --------------------------------//
//#######################################################################//

#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <math.h>

#include "WDT.h"
#include "Clock.h"
#include "EventSystem.h"
#include "MCU.h"
#include "GPIO.h"
#include "NVM.h"

#include "ADC.h"
#include "DAC.h"
#include "DMA.h"

#include "TC.h"
#include "RTC.h"

#include "SPI.h"
#include "TWI.h"
#include "USART.h"


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

