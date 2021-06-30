#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
void preset()
{
	PORTB=0x00;
	DDRB=0xFF;
}
int main(void)
{
    while(1)
    {
        PORTB=0xFF;
		_delay_ms(1000);
		PORTB=0x00;
		_delay_ms(1000);
    }
}