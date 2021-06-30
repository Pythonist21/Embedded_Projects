#ifndef UART_H_
#define UART_H_

//#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void port_init();
void uart_init();
void uart_transmit(unsigned char data);


#endif /* UART_H_ */