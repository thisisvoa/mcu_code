/*
 * config.c
 *
 *  Created on: 2017��8��16��
 *      Author: xiefei
 */
#include "usart.h"
#include "config.h"
#include "stm32f1xx_hal.h"

rtuParameter_t rtuParameter;

int8_t load_config(){


}

uint8_t upData_config(){
	/*
	 * ִ���������
	 */
	change_uart_baudrate(&RS2321_UART_HANDLE,rtuParameter.comBaudRate.baudRateRs2321);
	change_uart_baudrate(&RS2322_UART_HANDLE,rtuParameter.comBaudRate.baudRateRs2322);
	change_uart_baudrate(&RS4851_UART_HANDLE,rtuParameter.comBaudRate.baudRateRs4851);
	change_uart_baudrate(&RS4852_UART_HANDLE,rtuParameter.comBaudRate.baudRateRs4852);

	/*
	 * д��EEPROM
	 */

/*reStartMcu?*/
}




