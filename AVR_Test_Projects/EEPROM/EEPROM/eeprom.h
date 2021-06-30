#ifndef EEPROM_H_
#define EEPROM_H_

#define F_CPU 80000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

void eeprom_write(unsigned int uiAddress, unsigned char ucData);
unsigned char eeprom_read(unsigned int uiAddress);

#endif /* EEPROM_H_ */