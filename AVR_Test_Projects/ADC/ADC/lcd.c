#include "lcd.h"

void port_init(void)
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
	send_byte(0b00101000, 0); //4???-????? (DL=0) ? 2 ????? (N=1)
	_delay_ms(1);
	send_byte(0b00001100, 0); //???????? ??????????? ?? ??????? (D=1), ??????? ??????? ?? ???????? (C=0, B=0)
	_delay_ms(1);
	send_byte(0b00000110, 0); //?????? (???? ?? ? ??? ? ?????????) ????? ????????? ?????
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
	for(n=0; str1[n]!='\0'; n++)
	{
		send_char(str1[n]);
	}
}

void clear_lcd()
{
	send_byte(0b00000001, 0);
	_delay_us(1500);
}
