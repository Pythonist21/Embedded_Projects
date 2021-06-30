#define F_CPU 80000000UL

#include <avr/io.h>
#include "eeprom.h"
#include "uart.h"

int main(void)
{
	port_init();
	uart_init();
	asm("nop");
	eeprom_write(1, 120);
    while(1)
    {
        
    }
}