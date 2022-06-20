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
	
	//0~7까지의 숫자(16진수)
	int arr[] = {0xFD, 0x61, 0xDB, 0xF3, 0x67 , 0xB7, 0x3F, 0xE5};
	while(1)
	{
		if(PIND == 0x80)
		{
			PORTA =	arr[0]; //0b 1111 1101
		}
		else if(PIND == 0x40)
		{
			PORTA = arr[1]; //0b 0110 0001
		}
		else if(PIND == 0x20)
		{
			PORTA = arr[2]; //0b 1101 1011
		}
		else if(PIND == 0x10)
		{
			PORTA = arr[3]; //0b 1111 0011
		}
		else if(PIND == 0x08)
		{
			PORTA = arr[4]; //0b 0110 0111
		}
		else if(PIND == 0x04)
		{
			PORTA = arr[5]; //0b 1011 0111
		}
		else if(PIND == 0x02)
		{
			PORTA = arr[6]; //0b 0011 1111
		}
		else if(PIND == 0x01)
		{
			PORTA = arr[7]; //0b 1110 0101
		}
	}
	return 0;
	
}