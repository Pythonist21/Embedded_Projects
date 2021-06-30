#include "eeprom.h"
int *p;
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	{}
	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	//*p=ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE); /* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	while(EECR & (1<<EEWE))
	{} //ждем освобождения флага окончания последней операцией с памятью
	EEAR = uiAddress; //Устанавливаем адрес
	EECR |= (1<<EERE); //Запускаем операцию считывания из памяти в регистр данных
	return EEDR; //Возвращаем результат
}

void EEPROM_write_string(unsigned int uiAddress, char mas[])
{
	int lenght =sizeof(mas)/sizeof(mas[0]);
	*p=lenght;
	for(int i=0; i<lenght; i++)
	{
		EEPROM_write(uiAddress+i, mas[i]);
	}
}

/*
void EEPROM_write_word(unsigned int uiAddress, uint16_t ucData)
{
	EEPROM_write(uiAddress, (unsigned char) ucData);
	unsigned char dt = ucData>>8;
	EEPROM_write(uiAddress+, dt);
}
*/
uint16_t EEPROM_read_word(unsigned int uiAddress)

{
	uint16_t dt = EEPROM_read(uiAddress+1)*256;
	asm("nop");
	dt += EEPROM_read(uiAddress);
	return dt;
}

const char* EEPROM_read_string(unsigned int uiAddress, unsigned int cs)
{
	//unsigned int cs=6;
	//unsigned int sz=*p;
	char* str1=NULL;
	str1 = malloc(sizeof(char)*cs);
	for(unsigned int i=0; i<cs; i++)
	{
		str1[i]=EEPROM_read(uiAddress +i);
	}
	return str1;
}






