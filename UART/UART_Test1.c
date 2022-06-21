/*
 * UART_Test1.c
 *
 * Created: 2022-06-21 오전 9:35:56
 *  Author: PKNU
 */ 
#include <avr/io.h>

void putch(unsigned char data) //데이터 전송하는 함수
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

int main(void)
{
	unsigned char text[] = "Hello! World!! \r\n";
	unsigned char i =0;
	
	DDRE = 0xFE;	//RX(입력 0) Tx(출력 1)
	UCSR0A = 0x00;	//USARTn을 멀티프로세서 통신모드로 설정
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while(text[i] != '\0')
	{
		putch(text[i++]);
	}
}