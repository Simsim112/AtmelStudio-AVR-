/*
 * PWM4_PIEZO_SWITCH.c
 *
 * Created: 2022-06-23 오전 10:17:13
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 784, 880, 988, 1047};
volatile unsigned char sound_flag = 1;

int main()
{	
	DDRE = 0x08;
	
	TCCR3A = 0x00;
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30); // CTC모드, 프리스케일링 없음
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	EICRB = (1<< ISC71) | (1<< ISC70) | (1<< ISC61) | (1<< ISC60) | 
	(1<< ISC51) | (1<< ISC50) | (1<< ISC41) | (1<< ISC40); //외부인터럽트 7, 6, 5, 4 상승에지 인터럽트 발생
	EIMSK = (1 << INT7) | (1 << INT6) | (1 << INT5) | (1 << INT4); //외부 인터럽트 7, 6, 5, 4 허용
	EIFR= (1 << INTF7) | (1 << INTF6) | (1 << INTF5) | (1 << INTF4); //외부 인터럽트 발생여부 알려줌
	sei();
	while(1)
	{
		if(sound_flag)
		{
			OCR3C = ICR3/32;
			_delay_ms(2000);
			TCCR3A = 0x00; //부저 소리끔
			sound_flag = 0;
		}
	}
}
SIGNAL(INT4_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[0]/2;
	TCCR3A = 0x40; 
	sound_flag =1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[1]/2;
	TCCR3A = 0x40; 
	sound_flag =1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[2]/2;
	TCCR3A = 0x40;
	sound_flag =1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[3]/2;
	TCCR3A = 0x40; 
	sound_flag =1;
	sei();
}