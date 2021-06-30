#include "button.h"

static unsigned char but_cnt[5]={0};
void read_button_state(unsigned char b);
	
void init_button_timer(void)
{
	TIMSK |=(1<<TOIE0);
	TCCR0 |=(0<<CS02)|(1<<CS01)|(1<<CS00);
}

ISR(TIMER0_OVF_vect)
{
	read_button_state(Button_Right);
	read_button_state(Button_Up);
	read_button_state(Button_Down);
	read_button_state(Button_Left);
	read_button_state(Button_Select);
}

unsigned char read_button_press(unsigned char b)
{
	switch(b)
	{
		case Button_Right:
		if(adc_value<25)
			return ST_PRESSED;
		else
			return ST_UNPRESSED;
		break;
		case Button_Up:
		if((adc_value>25) && (adc_value<65))
			return ST_PRESSED;
		else
			return ST_UNPRESSED;
		break;
		case Button_Down:
		if((adc_value>65) && (adc_value<115)) 
			return ST_PRESSED;
		else
			return ST_UNPRESSED;
		break;
		case Button_Left:
		if((adc_value>115) && (adc_value<180))
			return ST_PRESSED;
		else
			return ST_UNPRESSED;
		break;
		case Button_Select:
		if((adc_value>180) && (adc_value<230))
			return ST_PRESSED;
		else
			return ST_UNPRESSED;
		break;
	}
	return ST_ERROR;
}

void read_button_state(unsigned char b)
{
	if ((button_state[b]&ST_LOCKED)!=0) return;
	if(read_button_press(b)==ST_UNPRESSED)
	{
		if (but_cnt[b]>0)
		{
			but_cnt[b]--;
		}
		else
		{
			if ((button_state[b]&ST_PRESSED)!=0)
			{
				button_state[b] |= ST_UNPRESSURE;
				button_state[b] &= ~ST_PRESSED;
				button_state[b] |= ST_UNPRESSED;
			}
		}
	}
	else
	{
		if (but_cnt[b]<5)
		{
			but_cnt[b]++;
		}
		else
		{
			if ((button_state[b]&ST_UNPRESSED)!=0)

			{
				button_state[b] |= ST_PRESSURE;
				button_state[b] &= ~ST_UNPRESSED;
				button_state[b] |= ST_PRESSED;

			}
		}
	}
}

//-----------------------------------------
void ResetButtonState(unsigned char b, unsigned char st)
{
	button_state[b]&=~st;
}
//-----------------------------------------
void SetButtonState(unsigned char b, unsigned char st)
{
	button_state[b]|=st;
}
//-----------------------------------------
void button_init(void)
{
	unsigned char i;
	//сбросим статусы кнопок
	for (i=0;i<5;i++)
	{
		button_state[i]=ST_UNPRESSED;
	}
	//запустим таймер
	init_button_timer();
}
