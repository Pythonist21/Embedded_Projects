#include "twi.h"

void twi_init(void)
{
	TWBR = 0x20;
}
void twi_start_cond(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&&(1<<TWINT)));
}

void twi_stop_cond(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}

void twi_send_byte(unsigned char c)
{
	TWDR = c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}

