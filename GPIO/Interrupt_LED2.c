/*
 * Interrupt_LED2.c
 *
 * Created: 2022-06-20 오전 10:39:44
 *  Author: PKNU
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char exchange = 0;

SIGNAL(INT4_vect)
{
	exchange = ~exchange;
}
int main()
{
	DDRE = 0x00;
	DDRA = 0xFF;
	EIMSK = (1 << INT4);
	EICRB = (1 << ISC41); //0b 0000 0010
	sei();
	PORTA = 0x01;
	while(1)
	{

		if(!exchange)
		{
			if(PORTA == 0x80)
			{
				PORTA = 0x01;
			}
			_delay_ms(500);
			PORTA = PORTA << 1;
		}
	}
	return 0;
}