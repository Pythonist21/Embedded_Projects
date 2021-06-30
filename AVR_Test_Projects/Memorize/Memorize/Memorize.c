#define F_CPU 8000000
#include <avr/io.h>

void port_init()
{
	DDRB = 0xFF;
	PORTB = 0x00;
}
int main(void)
{
    while(1)
    {
        for(int i=0; i<8; i++)
		{
			PORTB |=(1<<i);
		}
    }
}