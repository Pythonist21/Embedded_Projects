#include "spi.h"

void spi_init(void)
{
	DDRB|=((1<<PORTB4)|(1<<PORTB6)|(1<<PORTB7));//Ножки USI на выход
	DDRB&=~(1<<PORTB5);//Ножка DI на выход
	PORTB&=~((1<<PORTB4)|(1<<PORTB6)|(1<<PORTB7));//Ножки USI в низкий уровень
}

void spi_send_byte(char byte)
{
	USIDR = byte;
	USISR |=(1<<USIOIF);
	while(!(USISR&(1<<USIOIF)));
	{
		USICR |= ((1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC));//постепенно передаем байт
		_delay_us(10);
	}
}