/*
 * LCDgugudan.c
 *
 * Created: 2022-06-20 오후 4:16:05
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Lcd.h"

volatile unsigned char exchange =0;

SIGNAL(INT0_vect)
{
	exchange = ~exchange;
}

int main()
{
	DDRA = 0xFF;
	DDRG = 0xFF;
	char str1[20];
	Lcd_Init(); //LCD 초기화
	char str2[20] = "Interrupt Occur!";
	char str3[20] = " <Times Table>";
	DDRD = 0x00;
	EIMSK = (1 <<INT0);
	EICRA = (1 << ISC01);
	sei();

	while(1)
	{
		for(int i =1; i < 10;i++)
		{
			for(int j = 1; j < 10; j++)
			{
				if(!exchange)
				{
					Lcd_Clear();
					Lcd_Pos(0, 0);
					Lcd_STR(str3);
					Lcd_Pos(1, 0);
					sprintf(str1, "   %d * %d = %d",i ,j, i*j);
					Lcd_STR(str1);
					_delay_ms(500);
				}
				else
				{
					while(exchange)
					{
					Lcd_Clear();
					Lcd_Pos(0, 0);
					Lcd_STR(str2);
					_delay_ms(1000);
					}
				}
			}
		}
	}
	return 0;
}