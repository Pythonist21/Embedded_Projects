#include <avr/io.h>
#include "main.h"
#include <util/delay.h>
void port_init()
{
	DDRD = 0xFF;
	PORTD = 0x00;
}

int main(void)
{
	port_init();
	lcd_init();
    while(1)
    {
			set_pos(0,0);
			str_lcd("Diana");
			_delay_ms(1000);
			lcd_clear();
			set_pos(0,0);
			str_lcd("Go");
			_delay_ms(1000);
			lcd_clear();
			set_pos(0,0);
			str_lcd("V");
			_delay_ms(1000);
			lcd_clear();
			set_pos(0,0);
			str_lcd("Sraku!");
			_delay_ms(1000);
	}
}