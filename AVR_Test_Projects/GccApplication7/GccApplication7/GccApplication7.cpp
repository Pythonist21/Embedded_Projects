#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#define e1 PORTD|=0b00001000 // установка линии E в 1
#define e0 PORTD&=0b11110111 // установка линии E в 0
#define rs1 PORTD|=0b00000100 // установка линии RS в 1 (данные)
#define rs0 PORTD&=0b11111011

void port_init()
{
	DDRD = 0xFF;
	PORTD = 0x00;
}

void send_half_byte(unsigned char c)
{
	c<<=4;
	e1;
	_delay_us(50);
	PORTD&=0b00001111;
	PORTD|=c;
	e0;
	_delay_us(50);
}

void send_byte(unsigned char c, unsigned char mode)
{
	if (mode==0) 
	{
		rs0;
	}
	else 
	{
		rs1;
	}
	unsigned char hc=0;
	hc=c>>4;
	send_half_byte(hc); 
	send_half_byte(c);
}

void lcd_init()
{
	_delay_ms(15);
	send_half_byte(0b00000011);
	_delay_ms(4);
	send_half_byte(0b00000011);
	_delay_us(100);
	send_half_byte(0b00000011);
	_delay_ms(1);
	send_half_byte(0b00000010);
	_delay_ms(1);
	send_byte(0b00101000, 0); //4бит-режим (DL=0) и 2 линии (N=1)
	_delay_ms(1);	
	send_byte(0b00001100, 0); //включаем изображение на дисплее (D=1), курсоры никакие не включаем (C=0, B=0)
	_delay_ms(1);
	send_byte(0b00000110, 0); //курсор (хоть он у нас и невидимый) будет двигаться влево
	_delay_ms(1);
}

void send_char(unsigned char c)
{

	send_byte(c,1);

}

void set_pos(unsigned char x, unsigned y)
{
	 char adress;
	 adress=(0x40*y+x)|0b10000000;
	 send_byte(adress, 0);
}

void str_lcd (char str1[])
{
	unsigned int n;
	for(n=0; n<(strlen(str1)); n++)
	{
		send_char(str1[n]);
	}
}
int main(void)
{
	port_init();
	lcd_init();
	str_lcd("sosi hui!");
    while(1)
    {
        
    }
}