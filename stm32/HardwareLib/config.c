/*
 * config.c
 *
 *  Created on: 2017��8��16��
 *      Author: xiefei
 */
#include "usart.h"
#include "config.h"
#include "stm32f1xx_hal.h"
#include "AT24C04.h"

#define READ_NVM(SrcBuf,len,addr) Read_NByte_Randomaddress(SrcBuf,len,addr)
#define WRITE_NVM(addr,SrcBuf,len)

rtuParameter_t rtuParameter;

void control_io(uint8_t idx,uint8_t state){
	if(idx == 0){
		if(state){
			IO0_OUT_HIGH();
		}else{
			IO0_OUT_LOW();
		}

	}
	else if(idx ==1){
		if(state){
			IO1_OUT_HIGH();
		}else{
			IO1_OUT_LOW();
		}
	}
	else if (idx == 2){
		if(state){
			IO2_OUT_HIGH();
		}else{
			IO2_OUT_LOW();
		}
	}
	else if (idx == 3){
		if(state){
			IO3_OUT_HIGH();
		}else{
			IO3_OUT_LOW();
		}
	}

}

uint32_t convert_baudRate(uint8_t idx){

	switch(idx){

	case BAUD_2400:
		return 2400;

	case BAUD_4800:
		return 4800;

	case BAUD_9600:
		return 9600;

	case BAUD_14400:
		return 14400;

	case BAUD_19200:
		return 19200;

	case BAUD_57600:
		return 57600;

	case BAUD_115200:
		return 115200;

	default:break;
	}

	return 9600;
}

void upData_config(){
	/*
	 * ִ���������
	 */
	change_uart_baudrate(&RS2321_UART_HANDLE,
			convert_baudRate(rtuParameter.comBaudRate.baudRateRs2321));
	change_uart_baudrate(&RS2322_UART_HANDLE,
			convert_baudRate(rtuParameter.comBaudRate.baudRateRs2322));
	change_uart_baudrate(&RS4851_UART_HANDLE,
			convert_baudRate(rtuParameter.comBaudRate.baudRateRs4851));
	change_uart_baudrate(&RS4852_UART_HANDLE,
			convert_baudRate(rtuParameter.comBaudRate.baudRateRs4852));

	/*
	 * д��EEPROM
	 */

/*reStartMcu?*/

}

void load_config_Default(void){
	rtuParameter.comBaudRate.baudRateRs2321=BAUD_9600;
	rtuParameter.comBaudRate.baudRateRs2322=BAUD_9600;
	rtuParameter.comBaudRate.baudRateRs4851=BAUD_9600;
	rtuParameter.comBaudRate.baudRateRs4852=BAUD_9600;
	rtuParameter.sysConfig.lcdCloseTime=55;
	rtuParameter.sysConfig.lcdcloseBkTime=35;
	rtuParameter.sysConfig.mcuStopTime=60;
	rtuParameter.upDataArg.RtuStationAddr[0]=0;
	rtuParameter.upDataArg.RtuStationAddr[1]=12;
	rtuParameter.upDataArg.RtuStationAddr[2]=34;
	rtuParameter.upDataArg.RtuStationAddr[3]=12;
	rtuParameter.upDataArg.RtuStationAddr[4]=34;
	rtuParameter.upDataArg.centreStationAddr=0x01;
	rtuParameter.upDataArg.passWord = 1234;
	rtuParameter.upDataArg.rtuType = RTU_TYPE_SK; //ˮ��
	rtuParameter.upDataArg.timeAverageInterval=5; //5����


	 /*�����Ʒ�Ƶϵ��*/
	rtuParameter.rainGaugeParamater.rainGaugePsc=2;

	upData_config();
}
/*
 *return 0 success
 *return -1 fail
 */
int8_t load_config(void){
	if (READ_NVM((uint8_t*)(&rtuParameter),sizeof(rtuParameter),0x02))
		return 0;
	else
		return -1;
}




