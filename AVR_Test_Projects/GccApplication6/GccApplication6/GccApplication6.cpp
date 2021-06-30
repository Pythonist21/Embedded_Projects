#define F_CPU 1200000
#include <avr/io.h>
#include <util/delay.h>
void port_init()
{
	DDRB=0xFF;
}
int main(void)
{
	port_init();
    while(1)
    {
        PORTB =0xFF;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
    }
}