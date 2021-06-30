#include "main.h"
unsigned int adc_value=0; 

int main(void)
{
	port_init();
	adc_init();
	lcd_init();
	sei();
	float n;
    while(1)
    {
		set_pos(0,0);
        str_lcd(conversion(adc_value));
		set_pos(0,1);
		str_lcd("voltage:");
		n= (float) adc_value / 400;
		str_lcd(voltage_conv(n));
		//str_lcd(adc_value);
		/*
		 set_pos(0,1);
		 if(adc_value<25) str_lcd("RIGHT KEY");
		 else if(adc_value>40 && adc_value<80) str_lcd("UP KEY");
		 else if(adc_value>80 && adc_value<120) str_lcd("DOWN KEY");
		 else if(adc_value>120 && adc_value<160) str_lcd("LEFT KEY");
		 else if(adc_value>160 && adc_value<200) str_lcd("SELECTT KEY");
		 else
		 */ 
		_delay_ms(500);
    }
}