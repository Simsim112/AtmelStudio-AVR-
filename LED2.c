/*
 * LED2.c
 *
 * Created: 2022-06-17 오후 1:54:32
 *  Author: PKNU
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;
	PORTA = 0x01;
	while(1)
	{
		_delay_ms(1000);
		PORTA = PORTA << 1;
		if(PORTA == 0x80)
		{
			for(int i =0; i <7;i++)
			{
				_delay_ms(1000);
				PORTA = PORTA >> 1;
			}
		}

	}

	return 0;
}