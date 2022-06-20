/*
 * LED1.c
 *
 * Created: 2022-06-17 오전 11:45:00
 *  Author: PKNU
 */
#define F_CPU 7372800
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	DDRB = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	DDRC = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	DDRD = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	DDRE = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	DDRF = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	DDRG = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	
	
	while(1)
	{
		PORTA = 0xFF; //PORTA의 각 비트에 5V출력
		_delay_ms(1000);
		PORTA = 0x00; //PORTA의 각 비트에 5V출력
		_delay_ms(1000);
		PORTB = 0xFF;
		PORTC = 0xFF;
		PORTD = 0xFF;
		PORTE = 0xFF;
		PORTF = 0xFF;
		PORTG = 0xFF;

	}
	return 0;
}