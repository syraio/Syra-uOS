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
//------------------------------ String ---------------------------------//
//#######################################################################//

#include <string.h>

#define _MAX_STR_LENGTH_	2000

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------

#define _Str_Copy(so, si)		strlcpy((char*)so, si, sizeof(so))

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------

#define _unsafe_Str_Append_Ch(s, c)		{*s = c; s++; *s= 0;}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
char* _Tokenize(char* text, char ch);

#define _Next_Token()	_Tokenize(NULL, ',')

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
void _StrClearURL(char* s);

void _StrDelChar(char* s, char c);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- String Comparing Functions
int8_t _StrCmp(char* s, char* x);

int8_t _StrCmp_NC(char* s, char* x);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- String Copy Functions

char* strcpy_char(char* so, char* si, char ch, uint16_t so_size);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- String Appending Functions
void _StrAppend_Char(char* so, char ch, uint16_t so_size);
void _StrAppend(char* so, char* si, uint16_t so_size );
void _StrAppend_int(char* so, int32_t n, uint8_t len, uint16_t so_size);
void _StrAppend_Float(char* so, float f, uint8_t len, uint8_t lenD, uint16_t so_size);
void _StrAppend_Hex(char* so, uint8_t h, uint16_t so_size);

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- String Conversion Functions
int32_t _Str2N(char* s);
uint8_t _N2Str(int32_t n, char* s, uint8_t len);

void _F2Str(float f, char *s, uint8_t lnI, uint8_t lnD, uint8_t sign);
float _Str2F(char* s);

void _Hex2Str(char* so, uint8_t* h, uint16_t n);
uint8_t _Ch2Hex(char c);
char _Hex2Ch(uint8_t h);

void _Bin2Str(uint8_t h, char* so, uint16_t so_size);

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
