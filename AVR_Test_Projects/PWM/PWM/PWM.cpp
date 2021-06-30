#define F_CPU 8000000UL

#include "pwm.h"

int main(void)
{
	port_init();
	init_PWM_timer();
    while(1)
    {
		for(int i=0; i<255; i++)
		{
			OCR2++;
			_delay_ms(3);
		}
		for(int i=254; i>=0; i--)
		{
			OCR2--;
			_delay_ms(3);
		}
	}
}