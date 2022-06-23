/*
 * Step_Motor3.c
 *
 * Created: 2022-06-23 오후 3:24:41
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char Step[8] = {0x90,0x80,0xC0,0x40,0x60,0x20,0x30,0x10};
	
int main()
{
	unsigned char i, t =0;
	
	DDRD = 0xF0;
	while(1)
	{
		//1-2상 여자 방식(90도 회전 후 멈춤)
		for ( i = 0; i < 24 ; i++ )
		{
			PORTD = Step[t]; // 한 스텝 실행
			t++; // 다음 스텝 실행을 위해 t 증가
			if(t > 7) t = 0; // 8 스텝을 초과하지 않도록 초기화
			_delay_ms(10);
		}
		_delay_ms(1000);
	}
}