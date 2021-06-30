#include "main.h"
int main(void)
{
	spi_port_in();
	spi_init();
	timer_init(10);
	sei();
	_delay_ms(500);
    while(1)
    {
        for(int i=0; i<10000; i++)
		{
			led_print(i);
			_delay_ms(500);
		}
    }
}