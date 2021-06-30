#ifndef TWI_H_
#define TWI_H_

#include "main.h"

void twi_init(void);
void twi_start_cond(void);
void twi_stop_cond(void);
void twi_send_byte(unsigned char c);
#endif /* TWI_H_ */