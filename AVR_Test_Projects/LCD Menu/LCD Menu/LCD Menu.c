#include "main.h"

int main(void)
{
	port_init();
	lcd_init();
	adc_init();
	sei();
	set_pos(0,1);
	//send_char('h');
	//str_lcd("Dorov Hui");
	//_delay_ms(2000);
	clear_lcd();
    while(1)
    {
          set_pos(0,1);
          if(adc_value<25) str_lcd("RIGHT KEY");
          else if(adc_value<65) str_lcd("UP KEY");
          else if(adc_value<115) str_lcd("DOWN KEY");
          else if(adc_value<180) str_lcd("LEFT KEY");
          else if(adc_value<200) str_lcd("SELECTT KEY");
		  set_pos(0,0);
		  str_lcd(conversion(adc_value));
          _delay_ms(200);
    }
}