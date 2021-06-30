#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART_RXC_vect)
{
	if(UDR == 0b00000001)
	{
		PORTC = 0xFF;
	}
	else
	if(UDR == 0b00000000)
	{
		PORTC = 0x00;
	}
	else
	{
		PORTB =(1<<PB0);
	}
}
void preset()
{
	DDRD =(0<<PD0);  //rx на вход
	DDRD = (1<<PD1);    //tx на выход
	DDRC=0xFF;
	PORTC=0x00;
	DDRB=(1<<PB0);
}
void blut_init()
{
	//разрешаем прием, передачу, прерывание по приёму
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(0<<UDRIE);
	//8 бит данных, 1 стоп бит, без контроля четности
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	//Baud Rate: 9600
	UBRRL = 0x33;
	UBRRH = 0x00;
}
int main(void)
{
	preset();
	blut_init();
	sei();
	while(1)
	{
		
	}
}
