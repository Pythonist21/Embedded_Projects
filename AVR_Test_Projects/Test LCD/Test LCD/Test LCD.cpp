#define  F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	port_init();
	timer_init(125);
	sei();
    while(1)
    {
              for(int i=0; i<100; i++)
              {
	              led_print(i);
	              _delay_ms(500);
	              
              }
    }
}