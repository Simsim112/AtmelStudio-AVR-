/*
 * Time_Counter2.c
 *
 * Created: 2022-06-21 오후 3:59:33
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0, Shift_Flag=0;

SIGNAL(TIMER2_OVF_vect);

int main(void)
{
	DDRC = 0x0F;
	TCCR2 = 0x05;
	
	TCNT0 = 183; TIMSK = 0x40;
	TIFR |=1 << TOV2;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 = 183;
	timer2Cnt++;
	
	if(timer2Cnt == 50)
	{
		if(Shift_Flag == 0)
		{
			LED_Data <<= 1;
			if(LED_Data == 0x08)
			Shift_Flag = 1;
		}
		else
		{
			LED_Data >>= 1;
			if(LED_Data == 0x01)
			Shift_Flag = 0;
		}
		timer2Cnt=0;
	}
	sei();
}