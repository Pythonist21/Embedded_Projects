#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>
#include "seg.h"
int main(void)
{
	port_init();
    while(1)
    {
        for(int a=0; a<=9; a++)
		{
			seg_init(a);
			_delay_ms(1000);
		}
    }
}