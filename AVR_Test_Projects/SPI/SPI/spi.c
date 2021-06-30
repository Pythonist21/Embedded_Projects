#include "spi.h"
void spi_port_in(void)
{
	DDRB |= ((1<<PB2)|(1<<PB3)|(1<<PB5));
	PORTB &=~((1<<PB2)|(1<<PB3)|(1<<PB5));
}

void spi_init(void)
{
	SPCR = ((1<<SPE)|(1<<MSTR));
	SPDR =0b00000000;
}

void spi_send(unsigned int data)
{
	if(data>256)
	{
		exit(1);
	}
	 SPDR = data;
	 while(!(SPSR & (1<<SPIF)));
	 PORTB |= (1<<PB2); //������� �������
	 PORTB &= ~(1<<PB2); //������ �������
}

void spi_ind_symb(unsigned int i)
{
	switch(i)
	{
		case 1:
		SPDR =~0b00000110;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 2:
		SPDR =~0b01011011;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 3:
		SPDR =~0b01001111;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 4:
		SPDR =~0b01100110;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 5:
		SPDR =~0b01101101;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 6:
		SPDR =~0b01111101;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 7:
		SPDR =~0b00000111;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 8:
		SPDR =~0b01111111;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 9:
		SPDR =~0b01101111;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
		case 0:
		SPDR =~0b00111111;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2); //������� �������
		PORTB &= ~(1<<PB2); //������ �������
		break;
	}
}