#ifndef SPI_H_
#define SPI_H_

#include "main.h"
void spi_port_in(void);
void spi_init(void);
void spi_send(unsigned int data);
void spi_ind_symb(unsigned int i);
void timer_init(unsigned int speed);
void led_print(unsigned int number);
void segchar(unsigned char seg);
void set_reg(unsigned int count);
#endif /* SPI_H_ */