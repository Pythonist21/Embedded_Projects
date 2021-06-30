#include "spi.h"

void spi_init(void)
{
	DDRB|=((1<<PORTB4)|(1<<PORTB6)|(1<<PORTB7));//����� USI �� �����
	DDRB&=~(1<<PORTB5);//����� DI �� �����
	PORTB&=~((1<<PORTB4)|(1<<PORTB6)|(1<<PORTB7));//����� USI � ������ �������
}

void spi_send_byte(char byte)
{
	USIDR = byte;
	USISR |=(1<<USIOIF);
	while(!(USISR&(1<<USIOIF)));
	{
		USICR |= ((1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC));//���������� �������� ����
		_delay_us(10);
	}
}