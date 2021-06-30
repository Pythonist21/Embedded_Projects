#include "main.h"

int main(void)
{
	spi_port_in();
	spi_init();
	/*
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<PB2); //высокий уровень
	PORTB &= ~(1<<PB2); //низкий уровень
	SPDR = 0b11111111;
	PORTB |= (1<<PB2); //высокий уровень
	PORTB &= ~(1<<PB2); //низкий уровень
	_delay_ms(2000);
	*/
	//spi_send();
    while(1)
    {
		for(int i=0; i<10; i++)
		{
			spi_ind_symb(i);
			_delay_ms(500);
		}
		/*for(int i=0; i<256; i++)
		{
			spi_send(i);
			_delay_ms(100);
		}
		*/
		/*
		SPDR =0b00000000;
        while(!(SPSR & (1<<SPIF)));
        PORTB |= (1<<PB2); //высокий уровень
        PORTB &= ~(1<<PB2); //низкий уровень
		_delay_ms(2000);
        SPDR = 0b11111111;
		while(!(SPSR & (1<<SPIF)));
        PORTB |= (1<<PB2); //высокий уровень
        PORTB &= ~(1<<PB2); //низкий уровень
        _delay_ms(2000);
		*/
    }
}