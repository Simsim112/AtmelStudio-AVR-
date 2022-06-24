/*
 * keypadTest1.c
 *
 * Created: 2022-06-23 오후 4:03:58
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char keyScan();

int main()
{
	DDRA = 0xF8;				//0b 1<111 1><000> 포트 A 상위 4비트는 출력(ROW) 하위 3비트는 입력(Column)
	DDRC = 0xFF;
	unsigned char key;
	
	while(1)
	{
		key = keyScan();
		if(key == '1') PORTC = 0xFF;
		_delay_ms(1000);
	}
	
	return 0;
}

unsigned char keyScan()
{
	PORTA = 0xF7;						//0b 1111 0111
	if(PINA == 0xF6) return '1';		//0b 1111 0110;
	else if(PINA == 0xF5) return '2';	//0b 1111 0101;
	else if(PINA == 0xF3) return '3';	//0b 1111 0011;
	_delay_ms(100);
	
	PORTA = 0xEF;						//0b 1110 1111
	if(PINA == 0xEE) return '4';		//0b 1110 1110;
	else if(PINA == 0xED) return '5';	//0b 1110 1101;
	else if(PINA == 0xEB) return '6';	//0b 1110 1011;
	_delay_ms(100);
	
	PORTA = 0xDF;						//0b 1101 1111
	if(PINA == 0xDE) return '7';		//0b 1101 1110;
	else if(PINA == 0xDD) return '8';	//0b 1101 1101;
	else if(PINA == 0xDB)  return '9';	//0b 1101 1011;
	_delay_ms(100);
	
	PORTA = 0xBF;						//0b 1011 1111
	if(PINA == 0xBE) return '*';		//0b 1011 1110;
	else if(PINA == 0xBD)  return '0';	//0b 1011 1101;
	else if(PINA == 0xBB) return '#';	//0b 1011 1011;
	_delay_ms(100);
}