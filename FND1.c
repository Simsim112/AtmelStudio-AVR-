/*
 * FND1.c
 *
 * Created: 2022-06-17 오후 4:21:32
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include<avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD = 0x00;
	DDRA = 0xFF;
	
	while(1)
	{
		if(PIND == 0x80)
		{
			PORTA =	0xFD; //0b 1111 1101
		}
		else if(PIND == 0x40)
		{
			PORTA = 0x61; //0b 0110 0001
		}
		else if(PIND == 0x20)
		{
			PORTA = 0xDB; //0b 1101 1011
		}
		else if(PIND == 0x10)
		{
			PORTA = 0xF3; //0b 1111 0011
		}
		else if(PIND == 0x08)
		{
			PORTA = 0x67; //0b 0110 0111
		}
		else if(PIND == 0x04)
		{
			PORTA = 0xB7; //0b 1011 0111
		}
		else if(PIND == 0x02)
		{
			PORTA = 0x3F; //0b 0011 1111
		}
		else if(PIND == 0x01)
		{
			PORTA = 0xE5; //0b 1110 0101
		}
	}
	return 0;
	
}