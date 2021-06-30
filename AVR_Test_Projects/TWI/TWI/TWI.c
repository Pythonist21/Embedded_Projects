#include "main.h"

int main(void)
{
	twi_init();
	uart_init();
	//twi_start_cond();
	//uart_transmit(TWSR);
	//uart_transmit('h');
	int i = TWSR;
	uart_transmit_num(i);
	twi_start_cond(); //Отправим условие START
	uart_transmit_num(TWSR); //читаем статусный регистр
	twi_send_byte(0b10100000); //передаем адрес и бит записи (0)
	uart_transmit_num(TWSR); //читаем статусный регистр
	twi_send_byte(0);//переходим на 0x0000 – старший байт адреса памяти
	uart_transmit_num(TWSR); //читаем статусный регистр
	twi_send_byte(0); // – младший байт адреса памяти
	uart_transmit_num(TWSR); //читаем статусный регистр
	twi_stop_cond(); //Отправим условие STOP
	uart_transmit_num(TWSR); //читаем статусный регистр
    while(1)
    {
        //TODO:: Please write your application code 
    }
}