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
//--------------------------- TWI Driver --------------------------------//
//#######################################################################//

void TWI_Master_Create(TWI_t *pTwi, int32_t sys_speed, int32_t baud);
void TWI_Master_Config(TWI_t *pTwi, uint8_t int_cfg);
void TWI_Master_Disable(TWI_t *pTwi);

uint8_t TWI_Start(TWI_t *pTwi, uint8_t devAddr);
void TWI_Stop(TWI_t *pTwi, uint8_t ack);

uint8_t TWI_Send(TWI_t *pTwi, uint8_t data);
uint8_t TWI_Get(TWI_t *pTwi);

uint8_t TWI_Write(TWI_t *pTwi, uint8_t devAddr, uint8_t *data, uint8_t sz);

uint8_t TWI_Read(TWI_t *pTwi, uint8_t devAddr, uint8_t* data, uint8_t sz);


//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////

