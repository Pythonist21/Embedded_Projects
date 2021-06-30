#define F_CPU 8000000UL
#include "eeprom.h"
#include "uart.h"

int main(void)
{
	port_init();
	uart_init();
	//uart_transmit('h');
	//uart_transmit('u');
	//uart_transmit('i');
	//EEPROM_write(1, 75);
	//write_word(1,"rage");
	//unsigned char dat = EEPROM_read(1) ;
	//EEPROM_write_word(1, 30000);
	//uint16_t c = EEPROM_read_word(1);
	//uart_transmit(c);
	//uart_transmit(dat);
	EEPROM_write_string(1, "Per");
	const char *mas = EEPROM_read_string(1, 6);
	/*unsigned int z=sizeof(mas)/sizeof(mas[0]);
	for(int i=0; i<z; i++)
	{
		uart_transmit(mas[i]);
	}
	*/
	/*
	EEPROM_write(1, 'p');
	EEPROM_write(2, 'e');
	EEPROM_write(3, 't');
	EEPROM_write(4, 'o');
	EEPROM_write(5, 'n');
	const char *mas = EEPROM_read_string(1, 6);
	//unsigned int z=sizeof(mas)/sizeof(mas[0]);
	*/
	for(int i=0; i<6; i++)
	{
		uart_transmit(mas[i]);
	}
	//uart_transmit(EEPROM_read(3));
	while(1)
	{
		
	}
}