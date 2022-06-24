/*
 * DoorLock.c
 *
 * Created: 2022-06-24 오전 9:36:25
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Lcd.h"

volatile unsigned int i = 0;

unsigned int Open_Sound[3] = {1318, 659, 329};
	
unsigned int Error_Sound[3] = {523, 523, 523};

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

void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000
	PORTA = 0x07; //0b 0000 0111
}

unsigned char keyscan()
{
	PORTA = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01)  {return '1';}
	else if((PINA & 0x07) == 0x02) {return '2';}
	else if((PINA & 0x07) == 0x04) {return '3';}
	_delay_ms(10);
	
	PORTA = 0x10;		// 0x10
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) {return '4';}
	else if((PINA & 0x07) == 0x02) {return '5';}
	else if((PINA & 0x07) == 0x04) {return '6';}
	_delay_ms(10);
	
	PORTA = 0x20;		// 0x20
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) {return '7';}
	else if((PINA & 0x07) == 0x02) {return '8';}
	else if((PINA & 0x07) == 0x04) {return '9';}
	_delay_ms(10);
	
	PORTA = 0x40;		// 0x40
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) {return '*';}
	else if((PINA & 0x07) == 0x02) {return '0';}
	else if((PINA & 0x07) == 0x04) {return '#';}
	_delay_ms(10);
	
	return 0;
}

int main()
{
	DDRB = 0x80;	//PIEZO
	DDRD = 0xFF;	//LCD	
	DDRG = 0x0F;	//LCD
	DDRC = 0x0F;	//Step_Motor
	DDRE = 0x10;	//Interrupt
	init_keypad();
	Lcd_Init(); //LCD 초기화
	
	char str1[20] = "Doorlock system";
	char str2[20] = "Insert PW:";
	char str3[20] = "Open";
	char str4[20] = "Error number";

	//LCD 비밀번호 입력에 사용됨
	char key[4] = "";
	char pwd[4] ="1234";
	int compare = 0;
	char last = 0;
	char temp;
	//스텝 모터에 사용
	unsigned char j;
	
	//UART 연결
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	//PWM모드 설정
	TCCR1A |= (1 <<COM1C1) | (1 << WGM11); // Fast PWM 모드로 설정
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10); // A합쳐서 동작모드 설정, 프리스케일링 없음
	TCCR1C = 0x00;
	TCNT1 = 0x0000;
	
	EICRB = (1<< ISC41) | (1<< ISC40); //외부인터럽트 4 상승에지 인터럽트 발생
	EIMSK = (1 << INT4); //외부 인터럽트 4 허용
	EIFR = (1 << INTF4); //외부 인터럽트 발생여부 알려줌
	sei();
	
	while(1)
	{
		TCCR1A = 0x00; 
		temp = keyscan();
		_delay_ms(200);
		
		if(last != temp)
		{
			if(temp >= 48 && temp <= 57)
			{
				if(temp == '1')
				{
					last = key[i] = temp;
				}
				else if(temp == '2')
				{
					last = key[i] = temp;

				}
				else if(temp == '3')
				{
					last = key[i] = temp;

				}
				else if(temp == '4')
				{
					last = key[i] = temp;

				}
				else if(temp == '5')
				{
					last = key[i] = temp;

				}
				else if(temp == '6')
				{
					last = key[i] = temp;

				}
				else if(temp == '7')
				{
					last = key[i] = temp;

				}
				else if(temp == '8')
				{
					last = key[i] = temp;

				}
				else if(temp == '9')
				{
					last = key[i] = temp;

				}											
				i++;
			}
		}
		Lcd_Clear();
		Lcd_Pos(0, 0);
		Lcd_STR(str1);
		Lcd_Pos(1, 0);
		Lcd_STR(str2);
		Lcd_Pos(1, 10);
		Lcd_STR(key);
		_delay_ms(100);
		
		if(key[3] != NULL)
		{
			for(int i =0; i < 4;i++)
			{
				if(key[i] == pwd[i])
					compare++;
			}
			if(compare >= 1)
			{
				Lcd_Clear();
				Lcd_Pos(0, 0);
				Lcd_STR(str3);
				_delay_ms(500);
				//2상 여자 방식(시계방향으로 한바퀴 돌고 멈춤)
				for ( j = 0; j < 12 ; j++ ) // 48 스텝 실행
				{
					PORTC = 0x03; // 1 step 0b 0011 0000
					_delay_ms(10);
					PORTC = 0x09; // 2 step	0b 1001 0000
					_delay_ms(10);
					PORTC = 0x0C; // 3 step	0b 1010 0000
					_delay_ms(10);
					PORTC = 0x06; // 4 step	0b 0110 0000
					_delay_ms(10);
				}
				_delay_ms(1000);
				TCCR1A |= (1 <<COM1C1) | (1 << WGM11); // Fast PWM 모드로 설정
				for(int i =0; i < 4; i++)
				{
					ICR1 = 7372800 / Open_Sound[i];
					OCR1C = ICR1/32;
					_delay_ms(500);
				}
				TCCR1A = 0x00; 
			}
			else
			{
				Lcd_Clear();
				Lcd_Pos(0, 0);
				Lcd_STR(str4);
				_delay_ms(500);
				TCCR1A |= (1 <<COM1C1) | (1 << WGM11); // Fast PWM 모드로 설정
				for(int i =0; i < 4; i++)
				{
					ICR1 = 7372800 / Error_Sound[i];
					OCR1C = ICR1/32;
					_delay_ms(1000);
				}
				TCCR1A = 0x00;
			}
			while(1)
			{
				if(compare >= 1)
				{
					Lcd_Clear();
					Lcd_Pos(0, 0);
					Lcd_STR(str3);
					_delay_ms(500);
				}
				else
				{
					Lcd_Clear();
					Lcd_Pos(0, 0);
					Lcd_STR(str4);
					_delay_ms(500);
				}
			}
		}
	}
	return 0;
}

//SIGNAL(INT4_vect)
//{
//	cli();
//	
//	sei();
//}