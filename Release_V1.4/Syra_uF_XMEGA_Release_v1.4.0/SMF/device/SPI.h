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
//-------------------------------- SPI ----------------------------------//
//#######################################################################//

void SPI_Master_Create(SPI_t* pSpi, PORT_t* port, SPI_PRESCALER_t Prclr);

void SPI_Close(SPI_t* pSpi, PORT_t* port);


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void SPI_Config(SPI_t* pSpi, SPI_MODE_t md, SPI_INTLVL_t iLvl, uint8_t lsb);

uint8_t SPI_Transfer(SPI_t* pSpi, uint8_t dat);

uint16_t SPI_Print(SPI_t* pSpi, char* str);
uint16_t SPI_Print_P(SPI_t* pSpi, char* str);

void SPI_Write(SPI_t* pSpi, uint8_t* dataOut, uint16_t sz);
void SPI_Write_P(SPI_t* pSpi, uint8_t* dataOut, uint16_t sz);

void SPI_Read(SPI_t* pSpi, uint8_t dOut, uint8_t* dResp, uint16_t sz);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

