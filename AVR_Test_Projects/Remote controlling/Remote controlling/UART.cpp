#include "uart.h"

/*ISR(USART_RXC_vect)//Переривання по закiнченню передачі. Перевіряє вміст регістру UDR
{
	switch(UDR)
	{
		case '1':
		PORTC = (1<<PC0) | (1<<PC1);
		set_pos(7,0);
		str_lcd("ON");
		break;
		case '0':
		PORTC = 0x00;
		set_pos(7,0);
		str_lcd("OFF");
		break;
		default:
		PORTB =(1<<PB0);
		break;
	}
}
*/
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