/*
 * LED3.c
 *
 * Created: 2022-06-17 오후 2:17:30
 *  Author: PKNU
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;
	PORTA = 0xFF;
	int temp = 0x00;
	while(1)
	{
		_delay_ms(1000);
		PORTA = PORTA << 1;
	
		while(1)
		{
			_delay_ms(1000);
			PORTA = ((PORTA << 1) + 1);
		}
	}
	return 0;
}