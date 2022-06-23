/*
 * Step_Motor2.c
 *
 * Created: 2022-06-23 오후 3:18:35
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char i;
	
	DDRD = 0xF0;
	while(1)
	{
		//2상 여자 방식(시계방향으로 한바퀴 돌고 멈춤)
		for ( i = 0; i < 12 ; i++ ) // 48 스텝 실행
		{
			PORTD = 0x30; // 1 step 0b 0011 0000
			_delay_ms(10);
			PORTD = 0x90; // 2 step	0b 1001 0000
			_delay_ms(10);
			PORTD = 0xC0; // 3 step	0b 1010 0000
			_delay_ms(10);
			PORTD = 0x60; // 4 step	0b 0110 0000
			_delay_ms(10);	
		}
		_delay_ms(1000);
	}
}