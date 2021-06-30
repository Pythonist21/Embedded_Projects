#ifndef LCD_H_
#define LCD_H_
#include "main.h"

void lcd_init();
void send_char(unsigned char c);
void set_pos(unsigned char x, unsigned y);
void str_lcd(char str1[]);
void lcd_clear();

#endif /* LCD_H_ */