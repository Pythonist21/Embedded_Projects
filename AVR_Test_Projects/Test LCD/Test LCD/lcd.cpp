#include "lcd.h"

/*Для зміни ніжок індикації МК 
  внести зміни в port_init та
  цикл переривання
*/

unsigned int i;
unsigned char R1=0,R2=0;
unsigned char n_count=0;

ISR(TIMER1_COMPA_vect)
{
	if(n_count==0)
	{
		PORTB =0x00;
		PORTB &=~(1<<PB0);
		PORTB |=(1<<PB1);
		segchar(R1);
	}
	if(n_count==1)
	{
		PORTB =0x00;
		PORTB &=~(1<<PB1);
		PORTB|=(1<<PORTB0);
		segchar(R2);
	}
	n_count++;
	if(n_count>1)
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
	R2 = number/10;
}

void segchar(unsigned char seg)
{
	switch (seg)
	{
		case 1: PORTD = 0b11111001; break;
		case 2: PORTD = 0b10100100; break;
		case 3: PORTD = 0b10110000; break;
		case 4: PORTD = 0b10011001; break;
		case 5: PORTD = 0b10010010; break;
		case 6: PORTD = 0b10000010; break;
		case 7: PORTD = 0b11111000; break;
		case 8: PORTD = 0b10000000; break;
		case 9: PORTD = 0b10010000; break;
		case 0: PORTD = 0b11000000; break;
	}
}

void port_init()
{
	DDRB |= 1<<PB0 | 1<<PB1;
	DDRD = 0xFF;
}



