/*
 * UART_gugudan.c
 *
 * Created: 2022-06-21 오전 11:59:26
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <stdio.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) ==0);
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

int main(void)
{
	unsigned char text[] =
	"\r\n<Times Table Program>\r\n";
	
	unsigned char echo[] = "Enter Number >> ";
	unsigned char error[] = "\r\nPlease input 1~9\r\n";
	unsigned char Time_table[100];
	unsigned char i =0;
	unsigned char number;
	int num;
	DDRE = 0xFE;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while(1)
	{
		putchs(text);
		putchs(echo);
		number = getch();
		putch(number);
		if(number >= 49 && number <= 57)
		{
			num = (int)number - 48;
			
			for(int j =1;j < 10;j++)
			{
				sprintf(Time_table, "\r\n%d * %d = %d\r\n",num,j,num*j);
				putchs(Time_table);
			}
		}
		else
		{
			putchs(error);
		}
	}
}