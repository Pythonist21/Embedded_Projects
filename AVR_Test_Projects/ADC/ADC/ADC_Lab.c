#include "main.h"

int main(void)
{
	DDRC |=(0<<PC0);
	port_init();
	lcd_init();
	adc_init();
	//str_lcd("Piton Alles Gut");
    while(1)
    {
        set_pos(0,1);
		str_lcd(conversion(adc_conv()));
		float v =(float) adc_conv()/400; 
		set_pos(0,0);
		str_lcd("voltage:");
		str_lcd(voltage_conv(v));
		//int adc_value =adc_conv();
		//send_char(adc_value/1000+0x30);//����������� ����� � ��� �����
		//send_char((adc_value%1000)/100+0x30);//����������� ����� � ��� �����
		//send_char((adc_value%100)/10+0x30);//����������� ����� � ��� �����
		//send_char(adc_value%10+0x30);//����������� ����� � ��� �����
		_delay_ms(500);
    }
}