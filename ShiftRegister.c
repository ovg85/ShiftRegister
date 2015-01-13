#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define DATA 0
#define SCL 1
#define REC 2

#define SetPortBit(port, bit) port |= (1<<bit)

#define ClearPortBit(port, bit) port &= ~(1<<bit)

int main()
{
	unsigned int data=0;
	DDRD=0x07;	//PD0-PD2 как выход
	PORTD=0x00;	//Первоначально выключаем выход
	
	while(1)
	{
		_delay_ms(250);
		PORTB |= (1 << 0);

		SendData(data);	
		data=data+1;	
		_delay_ms(250);	
		PORTB &= ~(1 << 0);
	
	}
	return 1;
}

void SendData(unsigned int data)
{
	for (int i=0;i<16;i++)
	{
		if ((data&0x8000)==0x00)
			ClearPortBit(PORTD, DATA);
		else
			SetPortBit(PORTD, DATA);
		
		asm("nop");
		SetPortBit(PORTD, SCL);//Импульс на SCL
		asm("nop");
		ClearPortBit(PORTD, SCL);
		
		asm("nop");
		data=(data<<1);
	}
	asm("nop");
	SetPortBit(PORTD, REC);//Импульс на Latch clock
	asm("nop");
	ClearPortBit(PORTD, REC);
}

void pause (unsigned int a)	
{ unsigned int i;
 
for (i=a;i>0;i--)
;
}

