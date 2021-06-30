#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include <string.h>
#include "lcd.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
//#include "button.h"
unsigned int adc_value, adc_counter, adc_tmp;

#endif /* MAIN_H_ */