#ifndef SPI_H_
#define SPI_H_

#include "main.h"
void spi_port_in(void);
void spi_init(void);
void spi_send(unsigned int data);
void spi_ind_symb(unsigned int i);

#endif /* SPI_H_ */