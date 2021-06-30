#include "main.h"
void port_init()
{
	DDRD = 0xFF;
	PORTD = 0x00;
}

int main(void)
{
	port_init();
	lcd_init();
	str_lcd("Sosi!");
	while(1)
	{
		
	}
}