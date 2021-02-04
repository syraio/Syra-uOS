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
//-------------------------------- USART --------------------------------//
//#######################################################################//

typedef enum
{
	DTX = 0x01,
	DRX = 0x02,
	SPI_CLK = 0x04
}XUSART_PIN_CFG;

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------

void Usart_Create(USART_t* pUart, uint32_t sys_speed, uint32_t boud, XUSART_PIN_CFG pCfg);
void Usart_Close(USART_t* pUart);

void Usart_interrupt_Cfg(USART_t* pUart, USART_RXCINTLVL_t irx, USART_TXCINTLVL_t itx, USART_DREINTLVL_t iempty);


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------
void Usart_SPI_Config(USART_t* pUart, PORT_t* port, uint8_t clk_pin, uint8_t spi_mode, uint8_t lsb_first);

uint8_t Usart_SPI_Transfer(USART_t* pUart, uint8_t c);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------
void Usart_Send(USART_t* pUart, uint8_t c);

uint8_t Usart_Get(USART_t* pUart);

void Usart_Print(USART_t* pUart, char *s);

void Usart_Print_P(USART_t* pUart, const char *s);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
