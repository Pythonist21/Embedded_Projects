#include "main.h"

int main(void)
{
	unsigned char n;
	port_init();
	lcd_init();
	spi_init();
	str_lcd("It works!");
    while(1)
    {
		n=(unsigned char)rand()%256;
		char str[10];
		_delay_ms(1000);
		spi_send_byte(n);
		itoa(n,str,10);
		set_pos(0,1);
		str_lcd(str);
        //TODO:: Please write your application code 
    }
}