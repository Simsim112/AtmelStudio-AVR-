/*
 * Time_Counter16bit_3.c
 *
 * Created: 2022-06-22 오전 11:38:48
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
								0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
								0X79,0X71,0X08,0X80};
								
volatile unsigned char time_s = 0;

int main(void)
{
	DDRA = 0xFF;
	
	TCCR1A = 0x00;
	TCCR1B = (1 << CS12) | (1 << CS10); //프리스케일러 1024
	
	OCR1A = 7200;				//1초마다 한번씩 인터럽트 발생 7372800UL / 1024 = 7200
	TIMSK = (1 << OCIE1A);		//타이머 1과 출력비교 인터럽트 A
	TIFR |= 1 << OCF1A;			//타이머 발생 인터럽트 플래그 저장하는 레지스터
	
	sei();						//인터럽트 동작
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
}

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A = 7200;
	if(time_s > 17)
		time_s = 0;
	else
		time_s++;
		
	sei();
}