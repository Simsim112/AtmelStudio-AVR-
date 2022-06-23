/*
 * PWM_PEIZO_UART.c
 *
 * Created: 2022-06-23 오전 11:33:18
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
	
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
void putch_USART0(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 =data;
}
void putchs(char* str)
{
	while(*str != 0)
	{
		putch_USART0(*str);
		str++;
	}
}
int main()
{
	unsigned char number;
	int num;
	unsigned char error[] = "\r\nPlease input 1~9\r\n";
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	DDRB = 0x80;
	TCCR1A |= (1 <<COM1C1) | (1 << WGM11); // Fast PWM 모드로 설정
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10); // A합쳐서 동작모드 설정, 프리스케일링 없음
	TCCR1C = 0x00;
	TCNT1 = 0x0000;
	
	while(1)
	{
		number = getch();
		putch(number);
		if(number >= 49 && number <= 57)
		{
			num = (int)number - 48;
			
			if(num == 1)
			{
				ICR1 = 7372800 / DoReMi[0];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num == 2)
			{
				ICR1 = 7372800 / DoReMi[1];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num ==3)
			{
				ICR1 = 7372800 / DoReMi[2];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num ==4)
			{
				ICR1 = 7372800 / DoReMi[3];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num ==5)
			{
				ICR1 = 7372800 / DoReMi[4];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num ==6)
			{
				ICR1 = 7372800 / DoReMi[5];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num ==7)
			{
				ICR1 = 7372800 / DoReMi[6];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else if(num ==8)
			{
				ICR1 = 7372800 / DoReMi[7];
				OCR1C = ICR1/32;
				_delay_ms(250);
			}
			else
			{
				OCR1C = 0;
			}
			OCR1C = 0;
		}
	}
}