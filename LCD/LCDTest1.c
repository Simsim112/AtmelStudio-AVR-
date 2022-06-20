/*
 * LCDTest1.c
 *
 * Created: 2022-06-20 오후 2:55:00
 *  Author: PKNU
 */ 
 
 #define F_CPU 7372800UL
 #include <avr/io.h>
 #include <util/delay.h>
 #include "Lcd.h"
 
 int main()
 {
	 Byte *str1 = " LCD TEST";
	 Byte *str2 = " ATmega 128";
	 
	 DDRA = 0xFF;
	 DDRG = 0xFF;
	 
	 Lcd_Init(); //LCD 초기화
	 Lcd_Clear();
	 _delay_ms(1000);
	 
	 Lcd_Pos(0, 0); //커서 위치를 나타냄
	 Lcd_STR(str1);
	 Lcd_Pos(1, 0);
	 Lcd_STR(str2);
	 while(1)
	 {
	 }
	 return 0;
 }