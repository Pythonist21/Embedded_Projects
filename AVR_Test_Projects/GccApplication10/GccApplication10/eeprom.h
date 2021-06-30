#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
//#define F_CPU 8000000UL
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
uint16_t EEPROM_read_word(unsigned int uiAddress);
void EEPROM_write_string(unsigned int uiAddress, char mas[]);
const char* EEPROM_read_string(unsigned int uiAddress, unsigned int cs);
//void EEPROM_write_word(unsigned int uiAddress, uint16_t ucData);
//unsigned char *p;
//void write_word(unsigned int uiAddress, unsigned char *mas);

#endif /* EEPROM_H_ */
