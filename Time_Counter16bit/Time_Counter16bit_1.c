/*
 * Time_Counter16bit_1.c
 *
 * Created: 2022-06-22 오전 10:16:18
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt =0;

int main(void)
{
	DDRC = 0x0F;
	
	TCCR1A =0x00;
	TCCR1B = (1<< CS10);
	
	TCNT1 = 0;
	TIMSK = (1 << TOIE3);
	TIFR |=1 << TOV1;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	
	timer1Cnt++;
	
	if(timer1Cnt == 128)
	{
		LED_Data++;
		
		if(LED_Data > 0x0F)
			LED_Data = 0;
		
		timer1Cnt = 0;
	}
	sei();
	
}

