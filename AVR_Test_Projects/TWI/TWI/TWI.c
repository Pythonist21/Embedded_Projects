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
	twi_start_cond(); //�������� ������� START
	uart_transmit_num(TWSR); //������ ��������� �������
	twi_send_byte(0b10100000); //�������� ����� � ��� ������ (0)
	uart_transmit_num(TWSR); //������ ��������� �������
	twi_send_byte(0);//��������� �� 0x0000 � ������� ���� ������ ������
	uart_transmit_num(TWSR); //������ ��������� �������
	twi_send_byte(0); // � ������� ���� ������ ������
	uart_transmit_num(TWSR); //������ ��������� �������
	twi_stop_cond(); //�������� ������� STOP
	uart_transmit_num(TWSR); //������ ��������� �������
    while(1)
    {
        //TODO:: Please write your application code 
    }
}