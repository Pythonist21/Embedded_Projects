#ifndef PWM_H_
#define PWM_H_
//#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

void init_PWM_timer(void);
void port_init(void);

#endif 