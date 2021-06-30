#include "spi.h"

/*Для зміни ніжок індикації МК 
  внести зміни в port_init та
  цикл переривання
*/

unsigned int i;
unsigned char R1=0, R2=0, R3=0, R4=0;
unsigned char n_count=0;

ISR(TIMER1_COMPA_vect)
{
	if(n_count==0)
	{
		segchar(R1);
		SPDR = 0b00001110;
		while(!(SPSR & (1<<SPIF)));
		//set_reg(0);
		PORTB |= (1<<PB2); //высокий уровень
		PORTB &= ~(1<<PB2); //низкий уровень
	}
	if(n_count==1)
	{
		segchar(R2);
		SPDR = 0b00001101;
		while(!(SPSR & (1<<SPIF)));
		//set_reg(1);
		PORTB |= (1<<PB2); //высокий уровень
		PORTB &= ~(1<<PB2); //низкий уровень
	}
	if(n_count==2)
	{
		segchar(R3);
		SPDR = 0b00001011;
		while(!(SPSR & (1<<SPIF)));
		//set_reg(2);
		PORTB |= (1<<PB2); //высокий уровень
		PORTB &= ~(1<<PB2); //низкий уровень
	}
	if(n_count==3)
	{
		segchar(R4);
		SPDR = 0b00000111;
		while(!(SPSR & (1<<SPIF)));
		//set_reg(3);
		PORTB |= (1<<PB2); //высокий уровень
		PORTB &= ~(1<<PB2); //низкий уровень
	}
	n_count++;
	if(n_count>3)
	{
		n_count=0;
	}
}

void timer_init(unsigned int speed)
{
	TCCR1B |=(1<<WGM12);
	TIMSK |=(1<<OCIE1A);
	OCR1AH = speed; //записываем в регистр число для сравнения
	OCR1AL = 0b00000000;
	TCCR1B |=(1<<CS11);
}

void led_print(unsigned int number)
{
	R1 = number%10;
	R2 = number%100/10;
	R3 = number%1000/100;
	R4 = number/1000;
}

void segchar(unsigned char seg)
{
	switch (seg)
	{
			case 1:
			SPDR =~0b00000110;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 2:
			SPDR =~0b01011011;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 3:
			SPDR =~0b01001111;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 4:
			SPDR =~0b01100110;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 5:
			SPDR =~0b01101101;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 6:
			SPDR =~0b01111101;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 7:
			SPDR =~0b00000111;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 8:
			SPDR =~0b01111111;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 9:
			SPDR =~0b01101111;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
			case 0:
			SPDR =~0b00111111;
			while(!(SPSR & (1<<SPIF)));
			//PORTB |= (1<<PB2); //высокий уровень
			//PORTB &= ~(1<<PB2); //низкий уровень
			break;
	}
}
/*
void set_reg(unsigned int count)
{
	switch(count)
	{
		case 0:
		SPDR = 0b00001101;
		while(!(SPSR & (1<<SPIF)));
		break;
		case 1:
		SPDR = 0b00001101;
		while(!(SPSR & (1<<SPIF)));
		break;
		case 2:
		SPDR = 0b00001011;
		while(!(SPSR & (1<<SPIF)));
		break;
		case 3:
		SPDR = 0b00000111;
		while(!(SPSR & (1<<SPIF)));
		break;
	}
}
*/