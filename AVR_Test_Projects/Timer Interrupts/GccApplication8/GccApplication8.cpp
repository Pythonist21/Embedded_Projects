#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "seg.h"

unsigned int c=0;
ISR(TIMER1_COMPA_vect)
{
	if(c>9)
	{
		c=0;
	}
	seg_init(c);
	c++;
}
void timer_init()
{
	TCCR1B |=(1<<WGM12);
	TIMSK |=(1<<OCIE1A);
	OCR1AH = 0b10000000; //записываем в регистр число для сравнения
	OCR1AL = 0b00000000;
	TCCR1B |=(1<<CS12);
}
int main(void)
{
	port_init();
	timer_init();
	sei();
    while(1)
    {
        
    }
}