#define F_CPU 8000000UL
#include <avr/io.h>
#include "main.h"
#include "uart.h"
ISR(USART_RXC_vect)//Переривання по закiнченню передачі. Перевіряє вміст регістру UDR
{
	switch(UDR)
	{
		case '1':
		PORTC = (1<<PC0) | (1<<PC1);
		//lcd_clear();
		set_pos(0,0);
		str_lcd("POWER:ON");
		break;
		case '0':
		PORTC = 0x00;
		//lcd_clear();
		set_pos(0,0);
		str_lcd("POWER:OFF");
		break;
		default:
		PORTB =(1<<PB0);
		//lcd_clear();
		set_pos(0,0);
		str_lcd("WRONG SYMBOL!");
		break;
	}
}

void port_init()
{
	DDRD =0b11111110;  //rx на вход
	DDRC=0xFF;
	PORTC=0x00;
	DDRB=(1<<PB0);
}
int main(void)
{
	port_init();
	uart_init();
	lcd_init();
	sei();
    while(1)
    {
       
    }
}