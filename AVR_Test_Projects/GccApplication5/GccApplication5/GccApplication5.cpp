#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART_RXC_vect)
{
	switch(UDR)
	{
		case 'f':
		PORTB =(1<<PB0);
		break;
		
		case 'r':
		PORTB =(0<<PB0);
		break;
	}
}
void port_init()
{
	DDRB = 0xFF;
	PORTB =0x00;
}
int main(void)
{
	DDRD &= ~(1<<0);  //rx на вход
	DDRD |= (1<<1);    //tx на выход
	//разрешаем прием, передачу, прерывание по приёму
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(0<<UDRIE);
	//8 бит данных, 1 стоп бит, без контроля четности
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	//Baud Rate: 9600
	UBRRL = 0x33;
	sei();
	port_init();
	while(1)
	{
		
	}
}