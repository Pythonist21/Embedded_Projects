#include "uart.h"

/* 
ISR(USART_RXC_vect)//Переривання по закiнченню передачі. Перевіряє вміст регістру UDR
{
	switch(UDR)
	{
		case '1':
		PORTC = (1<<PC0) | (1<<PC1);
		break;
		case '0':
		PORTC = 0x00;
		break;
		default:
		PORTB =(1<<PB0);
		break;
	}
}
*/

void port_init()
{
	DDRD =(0<<PD0);  //rx на вход
	DDRD = (1<<PD1);    //tx на выход
	DDRC=0xFF;
	PORTC=0x00;
	DDRB=(1<<PB0);
}

void uart_init()
{
	//разрешаем прием, передачу, прерывание по приёму
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(0<<UDRIE);
	//8 бит данных, 1 стоп бит, без контроля четности
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	//Baud Rate: 9600
	UBRRL = 0x33;
	UBRRH = 0x00;
}

void uart_transmit(unsigned char data)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
}