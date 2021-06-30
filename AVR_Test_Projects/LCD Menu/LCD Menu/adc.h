#ifndef ADC_H_
#define ADC_H_

#include "main.h"
void adc_init(void);
unsigned int adc_conv(void);
char *conversion(unsigned int adc_value);
char *voltage_conv(float v);

#endif /* ADC_H_ */