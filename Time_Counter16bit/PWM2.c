/*
 * PWM2.c
 *
 * Created: 2022-06-22 오후 4:42:18
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Light = 0;
volatile unsigned char Light_flag = 1;
int main()
{
	
	DDRB = 0x80;
	
	DDRE = 0x00;
	
	TCCR2 = (1 << WGM20) | (1<< COM21) | (1 << CS21); // PWM모드, up카운팅일떄 clear OCn down카운팅일때 set Ocn
	TCNT2 = 0x00;
	
	EICRB = (1 << ISC71) | (1 << ISC70) | (1 << ISC61) | (1 << ISC60) |
	(1 << ISC51) | (1 << ISC50) | (1 << ISC41) | (1 << ISC40); // 7, 6, 5,4 상승 에지에서 인터럽트 발생
	
	EIMSK = (1 << INT7) | (1 << INT6) | (1 << INT5) | (1 << INT4); //7,6,5,4 인터럽트 허용
	
	EIFR = (1 << INTF7) | (1 << INTF6) | (1 << INTF5) | (1 << INTF4); //7,6,5,4 인터럽트 발생 여부 알려줌
	
	sei(); 
	while(1)
	{
		if(Light_flag)
		{
			OCR2 = Light;
			Light_flag = 0;
		}
	}
}

SIGNAL(INT4_vect)
{
	cli();
	Light = 0;
	Light_flag =1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	Light -= 51;
	if(Light < 0)
		Light = 0;
	Light_flag =1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	Light += 51;
	if(Light > 255)
		Light = 255;
	Light_flag =1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	Light = 255;
	Light_flag =1;
	sei();
}