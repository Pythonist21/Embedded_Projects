#include "adc.h"

void adc_init(void)
{
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADMUX |=(1<<REFS1)|(1<<REFS0);
}

unsigned int adc_conv(void)
{
	ADCSRA |=(1<<ADSC);
	while(ADCSRA &(1<<ADSC));
	return (unsigned int) ADC;
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