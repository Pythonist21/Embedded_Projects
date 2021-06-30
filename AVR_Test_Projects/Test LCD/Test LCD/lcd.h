#ifndef LCD_H_
#define LCD_H_

//#define  F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

void timer_init(unsigned int speed);
void led_print(unsigned int number);
void segchar(unsigned char seg);
void port_init();







#endif /* LCD_H_ */