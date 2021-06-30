#ifndef LCD_H_
#define LCD_H_
#define e1    PORTD|=0b00001000 // установка линии E в 1
#define e0    PORTD&=0b11110111 // установка линии E в 0
#define rs1    PORTD|=0b00000100 // установка линии RS в 1 (данные)
#define rs0    PORTD&=0b11111011 // установка линии RS в 0 (команда)

#include "main.h"

void lcd_init();
void send_char(unsigned char c);
void set_pos(unsigned char x, unsigned y);
void str_lcd(char str1[]);
void port_init();
void clear_lcd();

#endif /* LCD_H_ */