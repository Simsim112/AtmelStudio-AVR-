/*
 * Timer_COunter16bit_1.c
 *
 * Created: 2022-06-22 오전 11:18:34
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

int main(void)
{
	DDRC = 0x0F;
	
	TCCR3A =0x00;
	TCCR3B = (1<< CS32);
	
	TCNT3 = 36736;
	ETIMSK = (1 << TOIE3);
	ETIFR |=1 << TOV3;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER3_OVF_vect)
{
	cli();
	
	TCNT3 = 36736;
	LED_Data++;
		
	if(LED_Data > 0x0F)
		LED_Data = 0;

	sei();
	
}
