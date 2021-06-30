#include "main.h"

int main(void)
{
		unsigned char i=0;
		char str1[5][11]=
		{
			"RIGHT KEY \0",
			"UP KEY    \0",
			"DOWN KEY  \0",
			"LEFT KEY  \0",
			"SELECT KEY\0"
		};
		port_init(); //инициализируем порты
		lcd_init();  //инициализируем дисплей
		Adc_Init(); //инициализируем АЦП
		Button_ini(); //инициализируем состояние кнопок
		//init_button_timer();
		sei(); //включим глобальные прерывания
		clear_lcd(); //очистим дисплей
		set_pos(0,0);
		str_lcd("Button Test");
		while(1)
		{
			set_pos(0,1);
			for(i=0;i<5;i++)
			{
				if(button_state[i]&ST_UNPRESSURE)
				{
					//предотвратим обращение к кнопке из таймера во время выполнения обработчика
					SetButtonState(i,ST_LOCKED);
					str_lcd(str1[i]);
					ResetButtonState(i,ST_UNPRESSURE);
					SetButtonState(i,ST_PRESSURE);
					ResetButtonState(i,ST_LOCKED);
				}
			}
			_delay_ms(50);
		}
}