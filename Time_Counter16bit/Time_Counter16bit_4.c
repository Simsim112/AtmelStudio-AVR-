/*
 * Time_Counter16bit_4.c
 *
 * Created: 2022-06-22 오후 12:11:51
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
								0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
								0X79,0X71,0X08,0X80};
volatile unsigned char time_s = 0;
volatile unsigned char FND_Flag = 0, edge_flag = 0;

int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = (1 << ICES3) | (1 << CS32) | (1 << CS30); // 상승에지에서 검출, 프리스케일러 1024 
	ETIMSK = (1 << TICIE3);					//입력캡쳐 인터럽트를 개별적으로 Enable
	ETIFR |= 1 << ICF3;						//캡처 동작 수행시 1로 세트되고 입력캡처 인터럽트 발생
	
	sei();
	PORTA = FND_DATA_TBL[0];
	while(1)
	{
		if(FND_Flag)
		{
			if(time_s >= 15)
				time_s = 15;
				
			PORTA = FND_DATA_TBL[time_s];
			FND_Flag =0;
		}
	}
	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{
	cli();
	
	unsigned int count_check;
	
	if(edge_flag == 0)				//상승에지(스위치 누르면)
	{
		TCCR3B = (1 << CS32) | (1 << CS30); //프리스케일러 1024, 하강에지 캡처 트리거 
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}	
	else                           //하강에지(스위치 뗄때)
	{
		TCCR3B = (1 << ICES3) | (1 << CS32) | (1 << CS30); //상승에지 캡처 트리거, 프리스케일러 1024 
		count_check = ICR3;
		
		time_s = count_check/720;	//누를시간 0.1초 단위 변경 7372800/1024 = 7200Hz
		
		FND_Flag =1;
		edge_flag = 0;
	}
	sei();
}