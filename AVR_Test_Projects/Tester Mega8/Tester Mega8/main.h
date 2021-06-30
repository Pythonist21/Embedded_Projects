
#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include <string.h>
#include "lcd.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
unsigned int adc_value, adc_counter, adc_temp;

#endif /* MAIN_H_ */