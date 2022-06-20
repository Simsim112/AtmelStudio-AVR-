/*
 * Interrupt_7seg.c
 *
 * Created: 2022-06-20 오후 2:20:19
 *  Author: PKNU
 */ 
/*
 * Interrupt_FND2.c
 *
 * Created: 2022-06-20 오후 2:05:55
 *  Author: PKNU
 */ 
/*
 * Interrupt_FND1.c
 *
 * Created: 2022-06-20 오후 12:33:54
 *  Author: PKNU
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char exchange = 0;		

SIGNAL(INT4_vect)
{

}

int main()
{	
	DDRA = 0xFF;
	DDRE = 0x00;
	EIMSK = (1 << INT4);
	EICRB = (1<< ISC41);
	sei();
	
	while(1)
	{
		PORTA =0xFF;
	}

	return 0;
}