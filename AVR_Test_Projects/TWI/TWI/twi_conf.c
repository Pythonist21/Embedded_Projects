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
	TWDR = c;//������� ���� � ������� ������
	TWCR = (1<<TWINT)|(1<<TWEN);//������� �������� �����
	while (!(TWCR & (1<<TWINT)));//�������� ���� ����������� TWIN
}

