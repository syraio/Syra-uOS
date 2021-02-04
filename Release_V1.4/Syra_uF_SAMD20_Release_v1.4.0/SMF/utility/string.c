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
//------------------- Libraries
#include "sam.h"

#include "math.h"
#include "string.h"

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------
volatile char* _TOK_TEMP_PCHAR;
char* _Tokenize(char* text, char ch)
{
	if (text != NULL)
	{
		_TOK_TEMP_PCHAR = text;
	}
	else if (_TOK_TEMP_PCHAR == 0)
	{
		return 0;
	}
	
	if (*_TOK_TEMP_PCHAR == 0)
	{
		_TOK_TEMP_PCHAR = 0;
		return 0;
	}
	
	char* pCh = (char*)_TOK_TEMP_PCHAR;

	while (*_TOK_TEMP_PCHAR != 0)
	{
		if (*_TOK_TEMP_PCHAR == ch)
		{
			*_TOK_TEMP_PCHAR = 0;
			_TOK_TEMP_PCHAR++;
			break;
		}
		_TOK_TEMP_PCHAR++;
	}
	
	return pCh;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------	URL Encoding To ANSI
void _StrClearURL(char* s)
{
	char* pTmpStr;
	
	pTmpStr = s ;
	
	uint8_t x = 0;
	
	while(*s != 0)
	{
		if (*s == '%')
		{
			s++;
			x = _Ch2Hex(*s);
			x <<= 4 ;
			s++;
			x |= _Ch2Hex(*s) & 0x0F;
			s++;
			
			*pTmpStr = x ;
			pTmpStr++;
			
			x = 1;
		}
		else if(x > 0)
		{
			*pTmpStr = *s;
			
			pTmpStr++;
			s++;
		}
	}
	
	*pTmpStr = 0 ;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Delete char from string
void _StrDelChar(char* s, char c)
{
	char* pTmpStr;
	pTmpStr = s ;
	while(*s != 0)
	{
		if (*s != c)
		{
			*pTmpStr = *s ;
			pTmpStr++;
		}
		s++;
	}
	
	*pTmpStr = 0;
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Comparing strings - RAM_RAM
int8_t _StrCmp(char* s, char* x)
{
	while(1)
	{
		if (*x == 0)
		{
			if (*s == 0)
			{
				return 0 ;
			}
			
			return 1;
		}
		
		if (*s != *x)
		{
			if (*s == 0)
			{
				return -1 ;
			}
			
			return -2 ;
		}
				
		s++;
		x++;
	}	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Comparing strings in a case insensitive - RAM_RAM
int8_t _StrCmp_NC(char* s, char* x)
{
	while(1)
	{
		if (*x == 0)
		{
			if (*s == 0)
			{
				return 0 ;
			}
			
			return 1;
		}
		
		if (*s != *x)
		{
			if (*s == 0)
			{
				return -1 ;
			}
			
			if(((*s + 0x20) != *x) && (*s != (*x + 0x20)))
			{
				return -2 ;
			}
		}
		
		s++;
		x++;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Copy string until character - RAM to RAM
char* strcpy_char(char* so, char* si, char ch, uint16_t so_size)
{
	*so = 0;
	
	while(*si != 0)
	{		
		if (*si == ch)
		{
			si++;
			return si;
		}
		
		if (so_size > 1)
		{
			_unsafe_Str_Append_Ch(so , *si);
			
			so_size--;
		}
		
		si++;
	}
	
	return 0;	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Append the character ch at the end of so
void _StrAppend_Char(char* so, char ch, uint16_t so_size)
{
	while(so_size > 1)
	{
		if (*so == 0)
		{
			_unsafe_Str_Append_Ch(so , ch);
			
			break;
		}
		so++;
		
		so_size--;
	}	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Append string - RAM to RAM
void _StrAppend(char* so, char* si, uint16_t so_size)
{	
	while(so_size > 1)
	{
		if (*so == 0)
		{
			if (*si == 0)
			{
				break;
			}
			
			_unsafe_Str_Append_Ch(so , *si);
			
			si++;
		}
		else
		{
			so++;
		}
		
		so_size--;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Appending an Integer to String
void _StrAppend_int(char* so, int32_t n, uint8_t len, uint16_t so_size)
{
	uint8_t x = _Get_NumLen(n);
	if ( x < len)
	{
		x = len ;
	}
	
	while(so_size > x)
	{
		if (*so == 0)
		{
			_N2Str(n, so, len);
			break;
		}
		else
		{
			so++;
		}
		
		so_size--;
	}
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------  Appending a Float to String
void _StrAppend_Float(char* so, float f, uint8_t len, uint8_t lenD, uint16_t so_size)
{
	int8_t x = _Get_NumLen((int32_t)f);
	if ( x < len)
	{
		x = len ;
	}
	
	if (lenD > 0)
	{
		x += lenD + 1 ;
	}
	
	while(so_size > x)
	{
		if (*so == 0)
		{
			_F2Str(f, so, len, lenD, 0);
			break;
		}
		else
		{
			so++;
		}
		
		so_size--;
	}	
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------  Appending a HEX Byte to String
void _StrAppend_Hex(char* so, uint8_t h, uint16_t so_size)
{
	while(so_size > 2)
	{
		if (*so == 0)
		{
			*so = _Hex2Ch((h>>4) & 0x0f);
			so++;
			*so = _Hex2Ch(h & 0x0f);
			so++;
			*so = 0;
			break;
		}
		else
		{
			so++;
		}
		
		so_size--;
	}	
}


///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------  Convert String to integer
int32_t _Str2N(char* s)
{
	int32_t n, x ;
	uint8_t k, xlength;
	uint8_t sign = 1;

	while(*s == ' ')
	{
		s++;
	}
	
	if (*s == '-')
	{
		sign = 0 ;
		s++;
	}
	else if (*s == '+')
	{
		s++;
	}
	
	if (*s > '1')
	{
		xlength = 9;
	}
	else
	{
		xlength = 10;
	}
	
	n = 0 ;
	x = 0 ;
	k = 0 ;
	
	while (k < xlength)
	{
		if ((*s < '0')||(*s > '9'))
		{
			break;
		}
		
		x = n * 10 ;
		n = *s - '0';
		n += x ;
		
		s++;
		k++;
	}
	
	if (sign)
	{
		x = n;
	}
	else
	{
		x = -n ;
	}
	
	return x;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------  Convert integer to string
uint8_t _N2Str(int32_t n, char* s, uint8_t len)
{
	char* pStr = s;
	
	if (s != NULL)
	{
		int32_t x = n ;
		
		if (n < 0)
		{
			x = -n ;
			
			*s = '-';
			s++;
		}
		
		uint8_t c = 0 ;
		int8_t i = 10 ;
		int32_t j = 1000000000;
		while (i>0)
		{
			i--;
			n = x / j ;
			x -= n * j;
			if ((n > 0)||(i < len)||(c > 0))
			{
				c = n + '0' ;
				*s= c ;
				s++;
			}
			
			j /= 10 ;
		}
		
		*s = 0;		
	}
	
	return s - pStr;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Convert Float to string 0.7653
void _F2Str(float f, char *s, uint8_t lnI, uint8_t lnD, uint8_t sign)
{
	if (f < 0)
	{
		*s = '-';
		s++;
		f = -f ;
	}
	else if (sign)
	{
		*s = '+';
		s++;
	}
	
	sign = 1 ;
	
	int32_t x = (int32_t)f;
	_N2Str(x, s, lnI);
	
	f -= (float)x ;
	if ((f != 0)&&(lnD>0))
	{
		while (*s != 0)
		{
			s++;
		}
		*s = '.';
		s++;
		f = f * _Pow(10, lnD) ;
		x =(int32_t)f ;
		_N2Str(x, s, lnD);
	}
	
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Convert String to float
float _Str2F(char* s)
{
	while(*s == ' ')
	{
		s++;
	}
	
	uint8_t sign = 1;
	if (*s == '-')
	{
		sign = 0 ;
		s++;
	}
	else if (*s == '+')
	{
		s++;
	}

	uint8_t k ;
	float f, x, n ;
	k = 0;
	x = 0;
	n = 0;
	f = 0;
	while (1)
	{
		if ((*s < '0')||(*s > '9'))
		{
			break;
		}
		
		k++;
		if (k > 5)
		{
			return 0;
		}
		
		x = n*10 ;
		n= x + (*s - '0') ;
		s++;
	}
	f = n ;
	if (*s == '.')
	{
		s++;
		k = 0;
		n = 0;
		while (1)
		{
			k++;
			if ((*s < '0')||(*s > '9')||(k >5))
			{
				break;
			}
			x = n*10 ;
			n= x + (*s - '0') ;
			s++;
		}
		k--;
		x = n / _Pow(10, k) ;
		f += x ;
	}
	
	if (sign)
	{
		x = f;
	}
	else
	{
		x = -f ;
	}
	
	return x;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Convert Hex array to String
void _Hex2Str(char* so, uint8_t* h, uint16_t n)
{
	char c;
	while(n > 0)
	{
		c = ((*h)>> 4)& 0x0f ;
		*so = _Hex2Ch(c);
		so++;
		c = (*h) & 0x0f ;
		*so = _Hex2Ch(c);
		so++;
		
		h++;		
		n--;
	}
	
	*so = 0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Convert Char to Hex
uint8_t _Ch2Hex(char c)
{
	if((c >= '0') && ( c<= '9'))
	{
		return (c - '0' );
	}
	
	if((c >= 'a') && ( c<= 'f'))
	{
		return (c - 'a' + 10 );
	}
	
	if((c >= 'A') && (c <= 'F'))
	{
		return (c - 'A' + 10 );
	}
	
	return 0xF0;
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//------------------- Convert Hex to char
char _Hex2Ch(uint8_t h)
{
	if((h >= 0) && ( h <= 9 ))
	{
		return (h + '0' );
	}
	
	if((h >= 0x0a) && ( h<= 0x0f))
	{
		return (h - 0x0a + 'A');
	}
	
	return ' ';
}

///////////////////////////////////////////////////////////////////////////
//#######################################################################//
//-------------------  Convert binary byte to string
void _Bin2Str(uint8_t h, char* so, uint16_t so_size)
{
	for(uint8_t i=0; i<8; i++)
	{
		if ( so_size < 2)
		{
			break;
		}
		
		if (h & 0x80)
		{
			*so = '1';
		}
		else
		{
			*so = '0';
		}
		
		so++;
		*so = 0;
		
		h <<= 1 ;		
		
		so_size--;
	}	
}

//***********************************************************************//
//#######################################################################//
///////////////////////////////////////////////////////////////////////////
