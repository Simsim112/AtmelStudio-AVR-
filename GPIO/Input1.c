/*
 * Input1.c
 *
 * Created: 2022-06-17 오후 3:20:06
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD = 0x00;	//포트D를 입력으로 설정
	DDRA = 0xFF;	//포트A를 출력으로 설정
	while(1)
	{
		if(PIND == 0x01) 
		{
			PORTA = 0x01; //포트D 입력값이 0x01이면 포트A의 0번비트를 출력
			_delay_ms(300);
			PORTA = 0x00;
		}
		else if(PIND == 0x02)
		{
			PORTA = 0x03;
			_delay_ms(300);
			PORTA = 0x00;
		}
		else if(PIND == 0x04)
		{
			PORTA = 0x07;
			_delay_ms(300);
			PORTA = 0x00;
		}
	}
	return 0;
}