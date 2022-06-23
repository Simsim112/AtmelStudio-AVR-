/*
 * Step_Motor1.c
 *
 * Created: 2022-06-23 오후 3:05:40
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD = 0xF0;
	while(1)
	{
		//1상 여자 방식(계속 돌아감)
		PORTD = 0x10;
		_delay_ms(10);
		PORTD = 0x20;
		_delay_ms(10);
		PORTD = 0x40;
		_delay_ms(10);
		PORTD = 0x80;
		_delay_ms(10);
	}
}