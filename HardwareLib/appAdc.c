/*
 * appAdc.c
 *
 *  Created on: 2017��11��13��
 *      Author: Administrator
 */
#include "appAdc.h"

uint32_t ADC_getOriginalValue(uint8_t channelIdx){
	uint8_t i;
	for(i=0;i<=channelIdx;i++){
		HAL_ADC_Start(&hadc1);

		HAL_ADC_PollForConversion(&hadc1,20);
	}

	return HAL_ADC_GetValue(&hadc1);
}

float APP_ADC_getTemperature(){
	float res = 0;
	uint32_t adcValue = 0;
	adcValue = ADC_getOriginalValue(1);

	/*�¶�ת��*/
	res = (adcValue*3300/4096-760)/2.5+25;
	return res;
}

#define VBAT_ALLOT_RES_UP   10
#define VBAT_ALLOT_RES_DOWN 1

float APP_ADC_getMainBatteryVoltage(){
	uint32_t adcValue = 0;
	float res =0;

	float k_1 =(VBAT_ALLOT_RES_UP + VBAT_ALLOT_RES_DOWN) / VBAT_ALLOT_RES_DOWN ;

	adcValue = ADC_getOriginalValue(0);
	res = (((adcValue / 4096) * 2.5) * k_1);

	return res;
}


