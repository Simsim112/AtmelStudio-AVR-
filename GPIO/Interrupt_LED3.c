/*
 * Interrupt_LED3.c
 *
 * Created: 2022-06-20 오후 12:25:08
 *  Author: PKNU
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char shift_flag;

SIGNAL(INT4_vect)
{
	shift_flag = 1;
}
SIGNAL(INT5_vect)
{
	shift_flag = 2;
}
int main()
{
	char LED_DATA = 0x01;
	DDRE = 0x00;
	DDRA = 0xFF;
	EIMSK = (1<<INT5) | (1<<INT4);
	EICRB = (1 <<ISC50)| (1<<ISC51) | (1<<ISC41);
	sei();
	
	while(1)
	{
		PORTA = LED_DATA;
		if(shift_flag == 1)
		{
			if(LED_DATA == 0x80) LED_DATA = 0x01;
			else LED_DATA <<= 1;
		}
		else if(shift_flag == 2)
		{
			if(LED_DATA == 0x01) LED_DATA = 0x80;
			else LED_DATA >>= 1;
		}
		_delay_ms(100);
	}
	return 0;
}
