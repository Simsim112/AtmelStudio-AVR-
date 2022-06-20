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
volatile unsigned char cnt =0;			

SIGNAL(INT4_vect)
{
	exchange = 1;
	cnt = 0;
}
SIGNAL(INT5_vect)
{
	exchange = 0;
}

int main()
{
	unsigned char FND_DATA_TBL []={0x3F,0X06,0X5B,0X4F,0X66,0X6D,
									0X7C,0X07,0X7F,0X67};						
	DDRA = 0xFF;
	DDRE = 0x00;
	EIMSK = (1 << INT5) | (1 << INT4);
	EICRB = (1 << ISC51) | (1<<ISC50) | (1<< ISC41);
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		if(exchange == 0)
		{
			cnt++;
			if(cnt> 9) cnt =0;
		}
		_delay_ms(200);
	}

	return 0;
}