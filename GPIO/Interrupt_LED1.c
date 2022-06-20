/*
 * Interrupt_LED1.c
 *
 * Created: 2022-06-20 오전 9:55:28
 *  Author: PKNU
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char count = 0;;

SIGNAL(INT0_vect)
{
	count++;
	PORTA = count;
}
int main()
{
	DDRD = 0x00;
	DDRA = 0xFF;
	EIMSK = 0x01;	//INT0 활성
	//EIMSK = (1 << INT0);
	//EICRA = 0x03;	//0b 0000 0011
	EICRA = (1 << ISC01) | (1 << ISC00);	//0b 0000 0011
	sei();
	while(1)
	{

		
	}

	return 0;
}