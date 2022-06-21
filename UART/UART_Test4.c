/*
 * UART_Test4.c
 *
 * Created: 2022-06-21 오전 11:26:59
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
							0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};
				
void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch(void)
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main(void)
{
	unsigned char RX_Data = 0;
	DDRE = 0x0e;
	DDRA = 0xFF;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 3;
	while(1)
	{
		RX_Data = getch();
		
		if((RX_Data >= 0x30) && (RX_Data <= 0x39))
		{
			PORTA = FND_DATA_TBL[RX_Data - 0x30];
		}
	}
}