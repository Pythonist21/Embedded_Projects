#ifndef UART_H_
#define UART_H_

//#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void port_init();
void uart_init();
void uart_transmit(unsigned char data);
void uart_transmit_num(unsigned int num);

#endif /* UART_H_ */