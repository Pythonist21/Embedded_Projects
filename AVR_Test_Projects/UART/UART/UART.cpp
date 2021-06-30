#define F_CPU 8000000UL
#include <avr/io.h>
#include "uart.h"

ISR(USART_RXC_vect)
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

int main(void)
{
	port_init();
	uart_init();
	sei();
	 uart_transmit('p');
	 uart_transmit('i');
	 uart_transmit('d');
	 uart_transmit('o');
	 uart_transmit('r');
	 uart_transmit('!');
    while(1)
    {
         
    }
}