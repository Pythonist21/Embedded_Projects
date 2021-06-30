#include "adc.h"

extern unsigned int adc_value, adc_counter, adc_temp;
unsigned int adc_high=0, adc_low=0;

ISR(ADC_vect)
{
	adc_low = ADCL;
	adc_high = ADCH;
	//adc_value=adc_high*256+adc_low;
	if(adc_counter<20)
	{
		adc_temp+=adc_high;
		adc_counter++;
	}
	else
	{
		adc_value=adc_temp/20;
		adc_counter=0;
		adc_temp=0;
	}
}
void adc_init(void)
{
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADFR)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
	ADMUX |=(1<<ADLAR)|(1<<REFS1)|(1<<REFS0);
}

char *conversion(unsigned int adc_value)
{
	char *b=calloc(4, sizeof(char));
	b[0]=(adc_value/1000+0x30);
	b[1]=((adc_value%1000)/100+0x30);
	b[2]=((adc_value%100)/10+0x30);
	b[3]=(adc_value%10+0x30);
	return b;
}

char *voltage_conv(float v)
{
	char *c=calloc(4, sizeof(char));
	c[0]=((unsigned char) v+0x30);
	c[1]=('.');
	c[2]=((unsigned char)(v*10)%10+0x30);
	c[3]=((unsigned char)(v*100)%10+0x30);
	return c;
}